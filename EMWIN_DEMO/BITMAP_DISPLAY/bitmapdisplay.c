#include "bitmapdisplay.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK MiniSTM32开发板
//STemWin 绘制位图
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/4/15
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

extern GUI_BITMAP bmALIENTEK;  //ALIENTEK图标

//显示C文件格式的位图
void draw_bitmap(void)
{
	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_YELLOW);
	GUI_Clear();
	
	GUI_SetFont(&GUI_Font24_ASCII);
	GUI_SetTextMode(GUI_TM_TRANS);	//透明显示
	GUI_DispStringHCenterAt("ALIENTEK BITMAP DISPLAY",400,0 );
	
	GUI_DrawBitmap(&bmALIENTEK,50,50);  //绘制ALIENTEK图标	
}

//在显示器中缩放位图
//Xmag:X方向的比例因子，单位为千分之
//Ymag:Y方向的比例因子，单位为千分之
void zoom_bitmap(int Xmag,int Ymag)
{
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();
	GUI_DrawBitmapEx(&bmALIENTEK,400,240,105,46,Xmag,Ymag); //按照比例绘制位图
}
