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
 ALIENTEK MiniSTM32������STemWinʵ��
 STemWin ����λͼ

 UCOSIII���������ȼ��û�������ʹ�ã�ALIENTEK
 ����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
 ���ȼ�0���жϷ������������� OS_IntQTask()
 ���ȼ�1��ʱ�ӽ������� OS_TickTask()
 ���ȼ�2����ʱ���� OS_TmrTask()
 ���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
 ���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾
 ���ߣ�����ԭ�� @ALIENTEK
 ������¼��
 2016-11-28 �����˴��ڴ��flash��ͼƬ����������ʱ��϶�
 2016-11-29 �����˴�����Ӧλ��ʵ�ֲ�ͬ��ָ����Գɹ�
 2016-11-30 ������emwin����İ취������bmp��ʾ����ʱ������û����
 2016-12-1 ��������ֱ�Ӷ�rgb���ݵİ취��ʾͼƬ��ϣ��������ʱ�����ֻ���û���ã������ٶȱȽ���bmpͼƬ�ķ���������һ�롣
 2016-12-2 ������ֱ�ӻ��������棬�����ǿ��еģ��������������û�н���������ַ���������ʾ
 2017-1-12 ʵ�����������壬ֻ�����壬���ִ�С��ʽ�����ڿ������ʵ��������
 2017-1-13 д���������棬��ʵ������ת����ת֮����bug
 2017-1-14 ����˽�����ת֮���bug�������Ǻ�������������emwin�Դ��Ĵ��ڹ����������л�
 2017-1-24 ������ȫ���ĳ��˴��ڵ���ʽ������˽�����ת���߼���ջ���⣬��һ����������listwheel���в������
 2017-2-6  ���˴����Ķ���������multipage��edit��С���ߣ�ram�ռ�����е㲻���ˣ������mircroLib�����˹������ֽ��������ת�俨������
 2017-2-12 ����һЩ�����Զ�����ĳ�����ԭ�еĽ����������һ������
 2017-2-15 ���˴��������Զ��������ڵ����Ϸ������û�����ˣ�������ֲ����Ƭ����ʱ�������һ�����⣬���������������Ŀǰ��û���ҵ�ԭ��
           ��ֲ������ʱ��ͷ�ļ�Ҳ�д���˵���ظ������ˣ���Ҳû���ҵ�ԭ��
 �����ˣ�С�з
************************************************/
//�������ȼ�
#define START_TASK_PRIO				3
//�����ջ��С
#define START_STK_SIZE 				128
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//TOUCH����
//�����������ȼ�
#define TOUCH_TASK_PRIO				4
//�����ջ��С
#define TOUCH_STK_SIZE				128
//������ƿ�
OS_TCB TouchTaskTCB;
//�����ջ
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch����
void touch_task(void *p_arg);

//EMWINDEMO����
//�����������ȼ�
#define EMWINDEMO_TASK_PRIO			5
//�����ջ��С
#define EMWINDEMO_STK_SIZE			1024
//������ƿ�
OS_TCB EmwindemoTaskTCB;
//�����ջ
CPU_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task����
void emwindemo_task(void *p_arg);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO 				OS_CFG_PRIO_MAX-10
//�����ջ��С
#define LED0_STK_SIZE				128
//������ƿ�
OS_TCB Led0TaskTCB;
//�����ջ
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0����
void led0_task(void *p_arg);

void myScreen(void);
void startPage(void);

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();

	delay_init();	    	//��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			    //LED�˿ڳ�ʼ��
	TFTLCD_Init();			//LCD��ʼ��
	KEY_Init();	 			//������ʼ��
	mem_init();				//��ʼ���ڲ��ڴ��

	exfuns_init();			//Ϊfatfs�ļ�ϵͳ�����ڴ�
	f_mount(fs[0],"0:",1);	//����SD��
	f_mount(fs[1],"1:",1);	//����FLASH
	font_init();      //�����ʼ��
	TP_Init();				//��������ʼ��
	usmart_dev.init(72);

	OSInit(&err);			//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();	//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���
	OSStart(&err);  //����UCOSIII
	while(1);
}

//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);
#endif
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//����CRCʱ��
	GUI_Init();  			//STemWin��ʼ��

	OS_CRITICAL_ENTER();	//�����ٽ���
	//STemWin Demo����
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
	//����������
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
	//LED0����
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

	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����
	OS_CRITICAL_EXIT();	//�˳��ٽ���
}


//EMWINDEMO����
void emwindemo_task(void *pdata){
	//OS_ERR err;
//	GUI_MEMDEV_Handle hMem;
//	GUI_PID_STATE touchState;//����״̬
//	FIL fp;
//	char *buff;
//	unsigned int num;
//	buff=(char*)mymalloc(3840);
//	f_open(&fp,(const TCHAR*)"0:/SYSTEM/SYSICO/systemsetting.bin",FA_READ);//���ļ������ļ��������fp��

//	GUI_SetBkColor(GUI_BLUE);
//	GUI_SetColor(GUI_RED);
//	GUI_CURSOR_Show();
//	GUI_SetFont(&GUI_FontHZ16);
//	GUI_Clear();

	MainTask();
//	LCD_Scan_Dir(L2R_U2D);//������,���ϵ���
//	LCD_Set_Window(0,0,240,320);
//	LCD_SetCursor(0,0);//���ù��λ��
//	LCD_WriteRAM_Prepare();   	//��ʼд��GRAM
//
//	for(int y=0;y<40;y++){
//		f_read(&fp,buff,3840,(UINT*)&num);//���ļ������ݴ���������,�Լ��᲻�ϵ�����
//		for(int i=0;i<3840;i+=2){
//			LCD_WR_DATA(image_getcolor(0,(u8*)buff+i));
//		}
//		//f_lseek(&fp,fp.fptr+480);//f_read�ж�num�Ĳ����Ѿ�������ϵͳ�������ˣ�������Ҫ�ֹ�����
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

//TOUCH����
void touch_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		GUI_TOUCH_Exec();
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//��ʱ5ms
	}
}

//LED0����
void led0_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		LED0 = !LED0;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
	}
}
//void touchMeasure_task(void *p_arg){
//	OS_ERR err;
//	GUI_PID_STATE touchState;//����״̬
//	while(1){
//		LED1=!LED1;
//		GUI_PID_GetState(&touchState);
//		GUI_DispDecAt(touchState.x,10,50,6);//��ʾxֵ
//		GUI_DispDecAt(touchState.y,10,50+16,6);//��ʾyֵ
//		GUI_DispDecAt(touchState.Pressed,10,50+16+16,6);
////		GUI_DispDecAt(GUI_TOUCH_X_MeasureX(),10,50,6);
////		GUI_DispDecAt(GUI_TOUCH_X_MeasureY(),20,100,6);
//		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_PERIODIC,&err);//��ʱ50ms
//	}
//}

// void myScreen(void){
// 	//GUI_Init();
// 	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
// 	GUI_Clear();
// 	//����
// 	GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
// 	GUI_ClearRect(0, 109, 240, 320);
// 	//����
// 	GUI_SetPenSize(1);
// 	GUI_SetColor(MYCOLOR_LINE);
// 	GUI_DrawHLine(109, 0, 240);
// 	GUI_DrawHLine(160, 0, 240);
// 	GUI_DrawHLine(212, 0, 240);
// 	GUI_DrawLine(0, 262, 240, 262);
// 	//����
// 	GUI_SetColor(MYCOLOR_TITLE_TEXT);
// 	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
// 	GUI_SetFont(&GUI_FontHZ24);
// 	GUI_DispStringHCenterAt("ϵͳ����", 120, 51.6);
//
// 	GUI_SetColor(MYCOLOR_CONTENT_TEXT);
// 	GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
// 	GUI_SetFont(&GUI_FontHZ16);
// 	GUI_DispStringHCenterAt("��������", 120, 137.5-10);
// 	GUI_DispStringHCenterAt("ϵͳ����", 120, 188.2-10);
// 	GUI_DispStringHCenterAt("ϵͳ��Ϣ", 120, 239.8-10);
// 	GUI_DispStringHCenterAt("��������", 120, 293.4-10);
// }
