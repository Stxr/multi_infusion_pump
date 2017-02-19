#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "ILI93xx.h"
#include "usart.h"
#include "24cxx.h"
#include "flash.h"
#include "touch.h"
#include "timer.h"
#include "malloc.h"
#include "GUI.h"
#include "ff.h"
#include "MMC_SD.h"
#include "fontupd.h"
#include "exfuns.h"
#include "includes.h"
#include "bitmapdisplay.h"
#include "bmpdisplay.h"
#include "WM.h"
#include "DIALOG.h"
#include "usmart.h"
#include "image2lcd.h"
#include "mypage.h"

/************************************************
 ALIENTEK MiniSTM32开发板STemWin实验
 STemWin 绘制位图

 UCOSIII中以下优先级用户程序不能使用，ALIENTEK
 将这些优先级分配给了UCOSIII的5个系统内部任务
 优先级0：中断服务服务管理任务 OS_IntQTask()
 优先级1：时钟节拍任务 OS_TickTask()
 优先级2：定时任务 OS_TmrTask()
 优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
 优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司
 作者：正点原子 @ALIENTEK
 开发记录：
 2016-11-28 测试了从内存和flash读图片，发现所需时间较多
 2016-11-29 测试了触摸对应位置实现不同的指令，测试成功
 2016-11-30 试着用emwin储存的办法来减少bmp显示的延时，发现没卵用
 2016-12-1 测试了用直接读rgb数据的办法显示图片，希望减少延时，发现还是没卵用，加载速度比解码bmp图片的方法减少了一半。
 2016-12-2 测试了直接画出来界面，发现是可行的，就是字体的问题没有解决，中文字符还不能显示
 2017-1-12 实现了中文字体，只是宋体，三种大小格式，后期看情况再实现其他的
 2017-1-13 写了三个界面，并实现了跳转，跳转之间有bug
 2017-1-14 解决了界面跳转之间的bug，但不是很完美，打算用emwin自带的窗口管理器进行切换
 2017-1-24 将界面全部改成了窗口的形式，解决了界面跳转的逻辑堆栈问题，下一步打算利用listwheel进行插件整合
 2017-2-6  做了大量改动，引入了multipage和edit等小工具，ram空间好像有点不够了，编译给mircroLib打上了勾，发现界面间多次跳转变卡的问题
 2017-2-12 做了一些数据自动计算的程序，在原有的界面上添加了一个界面
 2017-2-15 做了大量数据自动化处理，在电脑上仿真基本没问题了，但是移植到单片机的时候出现了一点问题，可能是数据溢出，目前还没有找到原因，
           移植过来的时候头文件也有错误，说是重复调用了，但也没有找到原因。
 测试人：小螃蟹
************************************************/
//任务优先级
#define START_TASK_PRIO				3
//任务堆栈大小
#define START_STK_SIZE 				128
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//TOUCH任务
//设置任务优先级
#define TOUCH_TASK_PRIO				4
//任务堆栈大小
#define TOUCH_STK_SIZE				128
//任务控制块
OS_TCB TouchTaskTCB;
//任务堆栈
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch任务
void touch_task(void *p_arg);

//EMWINDEMO任务
//设置任务优先级
#define EMWINDEMO_TASK_PRIO			5
//任务堆栈大小
#define EMWINDEMO_STK_SIZE			1024
//任务控制块
OS_TCB EmwindemoTaskTCB;
//任务堆栈
CPU_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task任务
void emwindemo_task(void *p_arg);

//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO 				OS_CFG_PRIO_MAX-10
//任务堆栈大小
#define LED0_STK_SIZE				128
//任务控制块
OS_TCB Led0TaskTCB;
//任务堆栈
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0任务
void led0_task(void *p_arg);

void myScreen(void);
void startPage(void);

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();

	delay_init();	    	//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			    //LED端口初始化
	TFTLCD_Init();			//LCD初始化
	KEY_Init();	 			//按键初始化
	mem_init();				//初始化内部内存池

	exfuns_init();			//为fatfs文件系统分配内存
	f_mount(fs[0],"0:",1);	//挂载SD卡
	f_mount(fs[1],"1:",1);	//挂载FLASH
	font_init();      //字体初始化
	TP_Init();				//触摸屏初始化
	usmart_dev.init(72);

	OSInit(&err);			//初始化UCOSIII
	OS_CRITICAL_ENTER();	//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区
	OSStart(&err);  //开启UCOSIII
	while(1);
}

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);
#endif
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//开启CRC时钟
	GUI_Init();  			//STemWin初始化

	OS_CRITICAL_ENTER();	//进入临界区
	//STemWin Demo任务
	OSTaskCreate((OS_TCB*     )&EmwindemoTaskTCB,
				 (CPU_CHAR*   )"Emwindemo task",
                 (OS_TASK_PTR )emwindemo_task,
                 (void*       )0,
                 (OS_PRIO	  )EMWINDEMO_TASK_PRIO,
                 (CPU_STK*    )&EMWINDEMO_TASK_STK[0],
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE/10,
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK	  )0,
                 (void*       )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//触摸屏任务
	OSTaskCreate((OS_TCB*     )&TouchTaskTCB,
				 (CPU_CHAR*   )"Touch task",
                 (OS_TASK_PTR )touch_task,
                 (void*       )0,
                 (OS_PRIO	  )TOUCH_TASK_PRIO,
                 (CPU_STK*    )&TOUCH_TASK_STK[0],
                 (CPU_STK_SIZE)TOUCH_STK_SIZE/10,
                 (CPU_STK_SIZE)TOUCH_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK	  )0,
                 (void*       )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//LED0任务
	OSTaskCreate((OS_TCB*     )&Led0TaskTCB,
				 (CPU_CHAR*   )"Led0 task",
                 (OS_TASK_PTR )led0_task,
                 (void*       )0,
                 (OS_PRIO	  )LED0_TASK_PRIO,
                 (CPU_STK*    )&LED0_TASK_STK[0],
                 (CPU_STK_SIZE)LED0_STK_SIZE/10,
                 (CPU_STK_SIZE)LED0_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK	  )0,
                 (void*       )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);

	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务
	OS_CRITICAL_EXIT();	//退出临界区
}


//EMWINDEMO任务
void emwindemo_task(void *pdata){
	//OS_ERR err;
//	GUI_MEMDEV_Handle hMem;
//	GUI_PID_STATE touchState;//触摸状态
//	FIL fp;
//	char *buff;
//	unsigned int num;
//	buff=(char*)mymalloc(3840);
//	f_open(&fp,(const TCHAR*)"0:/SYSTEM/SYSICO/systemsetting.bin",FA_READ);//打开文件，将文件句柄放在fp中

//	GUI_SetBkColor(GUI_BLUE);
//	GUI_SetColor(GUI_RED);
//	GUI_CURSOR_Show();
//	GUI_SetFont(&GUI_FontHZ16);
//	GUI_Clear();

	MainTask();
//	LCD_Scan_Dir(L2R_U2D);//从左到右,从上到下
//	LCD_Set_Window(0,0,240,320);
//	LCD_SetCursor(0,0);//设置光标位置
//	LCD_WriteRAM_Prepare();   	//开始写入GRAM
//
//	for(int y=0;y<40;y++){
//		f_read(&fp,buff,3840,(UINT*)&num);//从文件将数据存入数组里,自己会不断的增加
//		for(int i=0;i<3840;i+=2){
//			LCD_WR_DATA(image_getcolor(0,(u8*)buff+i));
//		}
//		//f_lseek(&fp,fp.fptr+480);//f_read中对num的操作已经可以让系统连续读了，并不需要手工操作
// }
//	myfree(buff);
//	f_close(&fp);


	//hMem=GUI_MEMDEV_Create(0,0,240,320);
	//GUI_MEMDEV_Select(hMem);
	//dispbmpex("0:/SYSTEM/SYSICO/systemsetting.bmp",0,0,0,1,1);
	//GUI_MEMDEV_Select(0);
	//GUI_MEMDEV_CopyToLCDAt(hMem,0,0);
//	GUI_Delay(1000);
		//GUI_Clear();
}

//TOUCH任务
void touch_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		GUI_TOUCH_Exec();
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//延时5ms
	}
}

//LED0任务
void led0_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		LED0 = !LED0;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);//延时500ms
	}
}
//void touchMeasure_task(void *p_arg){
//	OS_ERR err;
//	GUI_PID_STATE touchState;//触摸状态
//	while(1){
//		LED1=!LED1;
//		GUI_PID_GetState(&touchState);
//		GUI_DispDecAt(touchState.x,10,50,6);//显示x值
//		GUI_DispDecAt(touchState.y,10,50+16,6);//显示y值
//		GUI_DispDecAt(touchState.Pressed,10,50+16+16,6);
////		GUI_DispDecAt(GUI_TOUCH_X_MeasureX(),10,50,6);
////		GUI_DispDecAt(GUI_TOUCH_X_MeasureY(),20,100,6);
//		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_PERIODIC,&err);//延时50ms
//	}
//}

// void myScreen(void){
// 	//GUI_Init();
// 	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
// 	GUI_Clear();
// 	//背景
// 	GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
// 	GUI_ClearRect(0, 109, 240, 320);
// 	//横线
// 	GUI_SetPenSize(1);
// 	GUI_SetColor(MYCOLOR_LINE);
// 	GUI_DrawHLine(109, 0, 240);
// 	GUI_DrawHLine(160, 0, 240);
// 	GUI_DrawHLine(212, 0, 240);
// 	GUI_DrawLine(0, 262, 240, 262);
// 	//字体
// 	GUI_SetColor(MYCOLOR_TITLE_TEXT);
// 	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
// 	GUI_SetFont(&GUI_FontHZ24);
// 	GUI_DispStringHCenterAt("系统设置", 120, 51.6);
//
// 	GUI_SetColor(MYCOLOR_CONTENT_TEXT);
// 	GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
// 	GUI_SetFont(&GUI_FontHZ16);
// 	GUI_DispStringHCenterAt("个性设置", 120, 137.5-10);
// 	GUI_DispStringHCenterAt("系统升级", 120, 188.2-10);
// 	GUI_DispStringHCenterAt("系统信息", 120, 239.8-10);
// 	GUI_DispStringHCenterAt("关于我们", 120, 293.4-10);
// }
