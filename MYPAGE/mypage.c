#include "mypage.h"
#define MYCOLOR_TITLE_BACKGROUND 0Xf1edec
#define MYCOLOR_TEXT_BACKGROUND 0Xffffff
#define MYCOLOR_TITLE_TEXT 0X3e4040
#define MYCOLOR_LINE  0Xf0f0f0
#define MYCOLOR_CONTENT_TEXT 0X4a4a4a
#define MYCOLOR_PAGEHOME_TITLE_BACKGROUND 0xf1edec
#define MYCOLOR_PAGEHOME_SHUYE_BACKGROUND 0x98593b
#define MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND 0x47b6c7
#define MYCOLOR_PAGEHOME_TITLE_TEXT 0x484848
#define MYCOLOR_PAGEHOME_SETTING_TEXT 0xe5e5e
#define MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND MYCOLOR_PAGEHOME_TITLE_BACKGROUND
#define MYCOLOR_PAGESHUYESETTING_CONTENT GUI_WHITE
#define MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND 0xf5b712
#define MYCOLOR_PAGESHUYESETTING_TITLE_TEXT MYCOLOR_PAGEHOME_TITLE_TEXT
#define MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT1 0x333333
#define MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2 0x98593b
#define MYCOLOR_PAGEDISPLAY_BACKGROUND 0xf1edec
#define MYCOLOR_PAGEDISPLAY_BUTTON MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND
#define MYCOLOR_PAGEDISPLAY_TEXT1 0x484848
#define MYCOLOR_PAGEDISPLAY_TEXT2 0x93837f
#define MYCOLOR_PAGEDISPLAY_TEXT3 0x47b6c7

//static WM_CALLBACK * _cbBkWindowOld;


//���ھ��
//static WM_HWIN _hWindow1;  	//����1
//static WM_HWIN _hWindow2;	//����2
//static WM_HWIN _hChild1;		//�Ӵ���1

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
// void MainTask(void) {
// 	GUI_Init();
// 	WM_EnableMemdev(WM_HBKWIN); //���ô����豸
//
// }
void W_pageDisplay(void) {
	WM_HWIN hWnd;
	GUI_PID_STATE touchState;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageDisplay, 0);
	GUI_Exec();
	while (1)
	{
		GUI_Delay(20);
		GUI_PID_GetState(&touchState);
		if (touchState.Pressed == 1) {
			while (touchState.Pressed == 1) {
				GUI_PID_GetState(&touchState);
			}
			if (touchState.y >= 296) {
				if (touchState.x < 120) {
					WM_DeleteWindow(hWnd);
					break;
				}
				else
				{

				}
			}
		}
	}
}
void W_pageHome(void) {
	WM_HWIN hWnd;
	GUI_PID_STATE touchState;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageHome, 0);
	GUI_Exec();
	while (1)
	{
		GUI_Delay(50);
		GUI_PID_GetState(&touchState);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_SetColor(GUI_YELLOW);
		if (touchState.Pressed == 1) {
			while (touchState.Pressed == 1) {
				GUI_PID_GetState(&touchState);
			}
			if (touchState.y < 259 && touchState.y>197) {//��Һ����
			//	GUI_DispStringAt("succeed", 0, 10);
//				WM_HideWindow(hWnd);
//				WM_DeleteWindow(hWnd);//ɾ������
				W_pageShuyeSetting();
			}
			else if (touchState.y > 259 && touchState.y < 320) {//ϵͳ����
																//GUI_DispStringAt("1", 0, 0);
				W_pageSetting();
			}
		}
	}
}
void W_pageSetting(void) {
	WM_HWIN hWnd;
	GUI_PID_STATE touchState;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageSetting, 0);
	GUI_Exec();
	GUI_SetColor(MYCOLOR_TITLE_TEXT);
	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
	while (1)
	{
		GUI_Delay(20);
		GUI_PID_GetState(&touchState);
		if (touchState.Pressed == 1) {
			while (touchState.Pressed == 1) {
				GUI_PID_GetState(&touchState);
			}
			if (touchState.y < 17.9&&touchState.x>191) {
				GUI_DispStringAt("0", 0, 0);
			}
			else if (touchState.y > 108 && touchState.y < 150) {
				GUI_DispStringAt("1", 0, 0);
			}
			else if (touchState.y >= 150 && touchState.y<193) {
				GUI_DispStringAt("2", 0, 0);
			}
			else if (touchState.y >= 193 && touchState.y <= 235) {
				GUI_DispStringAt("3", 0, 0);
			}
			else if (touchState.y >= 235 && touchState.y <= 278) {
				GUI_DispStringAt("4", 0, 0);
			}
			else if (touchState.y >= 278) {
				WM_DeleteWindow(hWnd);
				break;
			}
		}
	}

}
void W_pageShuyeSetting(void) {
	WM_HWIN hWnd;
	GUI_PID_STATE touchState;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageShuyeSetting, 0);
	GUI_Exec();
	while (1){
		GUI_Delay(50);
		GUI_PID_GetState(&touchState);
		if (touchState.Pressed == 1) {
			while (touchState.Pressed == 1) {
				GUI_PID_GetState(&touchState);
			}
			if (touchState.y >= 296) {
				if (touchState.x < 120) {
					WM_DeleteWindow(hWnd);
					break;
				}
				else {
					W_pageDisplay();
				}
			}
		}
	}

}
void pageShuyeSetting(WM_MESSAGE *pMsg) {
	switch (pMsg->MsgId){
		case WM_PAINT:
			GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
			GUI_Clear();

			//����
			GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_CONTENT);
			GUI_ClearRect(0, 85, 240, 296);
			GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
			GUI_ClearRect(0, 296, 240, 320);
			//����
			GUI_SetPenSize(1);
			GUI_SetColor(MYCOLOR_LINE);
			GUI_DrawHLine(85, 0, 240);
			GUI_DrawHLine(136, 0, 240);
			GUI_DrawHLine(187, 0, 240);
			GUI_DrawHLine(238, 0, 240);
			GUI_DrawHLine(295, 0, 240);
			GUI_SetColor(GUI_WHITE);
			GUI_DrawVLine(120, 296, 320);
			//д��
			GUI_SetColor(MYCOLOR_PAGESHUYESETTING_TITLE_TEXT);
			GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
			GUI_SetFont(&GUI_FontHZ24);
			GUI_DispStringHCenterAt("��ʼ����", 120, 40);

			GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT1);
			GUI_SetBkColor(GUI_WHITE);
			GUI_SetFont(&GUI_FontHZ16);
			GUI_DispStringHCenterAt("1��ƿ", 36, 105);
			GUI_DispStringHCenterAt("2��ƿ", 36, 156);
			GUI_DispStringHCenterAt("3��ƿ", 36, 207);
			GUI_DispStringHCenterAt("4��ƿ", 36, 258);

			GUI_SetColor(GUI_WHITE);
			GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
			GUI_DispStringHCenterAt("����", 60, 300);
			GUI_DispStringHCenterAt("ȷ��", 180, 300);

			GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
			GUI_SetBkColor(GUI_WHITE);
			GUI_SetFont(&GUI_FontHZ16);
			GUI_DispStringAt("����:        ml", 85, 90);
			GUI_DispStringAt("ʱ��:            ", 85, 110);//delt=20
			GUI_DispStringAt("����:        ml", 85, 140);
			GUI_DispStringAt("ʱ��:            ", 85, 160);//delt=20
			GUI_DispStringAt("����:        ml", 85, 193);
			GUI_DispStringAt("ʱ��:            ", 85, 213);//delt=20
			GUI_DispStringAt("����:        ml", 85, 243);
    	GUI_DispStringAt("ʱ��:            ", 85, 263);//delt=20
			break;
	  default:
			break;
	}
}
void pageHome(WM_MESSAGE *pMsg) {
	switch (pMsg->MsgId){
		case WM_PAINT:
			GUI_SetBkColor(MYCOLOR_PAGEHOME_TITLE_BACKGROUND);
			GUI_Clear();

			//����
			GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
			GUI_ClearRect(0, 197, 240, 259);
			GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
			GUI_ClearRect(0, 259, 240, 320);

			//����
			GUI_SetPenSize(1);
			GUI_SetColor(MYCOLOR_LINE);
			GUI_DrawHLine(197, 0, 240);
			GUI_DrawHLine(259, 0, 240);

			//д��
			GUI_SetColor(MYCOLOR_PAGEHOME_TITLE_TEXT);
			GUI_SetBkColor(MYCOLOR_PAGEHOME_TITLE_BACKGROUND);
			GUI_SetFont(&GUI_FontHZ24);
			GUI_DispStringHCenterAt("Multi-ȫ�Զ� ", 120, 70);
			GUI_DispStringHCenterAt(" ������Һ�� ", 120, 100);

			GUI_SetColor(MYCOLOR_PAGEHOME_SETTING_TEXT);
			GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
			GUI_SetFont(&GUI_FontHZ16);
			GUI_DispStringHCenterAt(" ��Һ���� ", 120, 218);
			GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
			GUI_DispStringHCenterAt(" ϵͳ���� ", 120, 280);
			break;
		default:
			break;
	}
}
void pageSetting(WM_MESSAGE *pMsg) {
	switch (pMsg->MsgId){
		case WM_PAINT:
			GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
			GUI_Clear();
			GUI_SetFont(&GUI_Font32_ASCII);
			//GUI_DispString("hello,emwin");
			//������
			GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
			GUI_ClearRect(0, 109, 240, 320);
			//����
			GUI_SetPenSize(1);
			GUI_SetColor(MYCOLOR_LINE);
			GUI_DrawHLine(109, 0, 240);
			GUI_DrawHLine(150, 0, 240);
			GUI_DrawHLine(193, 0, 240);
			GUI_DrawLine(0, 235, 240, 235);
			GUI_DrawHLine(278, 0, 240);
			//д��
			GUI_SetColor(MYCOLOR_TITLE_TEXT);
			GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
			GUI_SetFont(&GUI_FontHZ24);
			GUI_DispStringHCenterAt("ϵͳ����", 120, 51.6);

			GUI_SetColor(MYCOLOR_CONTENT_TEXT);
			GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
			GUI_SetFont(&GUI_FontHZ16);
			GUI_DispStringHCenterAt("�������� ", 120, 108 + 10);
			GUI_DispStringHCenterAt("ϵͳ���� ", 120, 150.4 + 10);
			GUI_DispStringHCenterAt("ϵͳ��Ϣ", 120, 192.8 + 10);
			GUI_DispStringHCenterAt("��������", 120, 235.2 + 10);
			GUI_DispStringHCenterAt("����", 120, 277.6 + 10);
			break;
		default:
			break;
	}
}
void pageDisplay(WM_MESSAGE *pMsg) {
	switch (pMsg->MsgId){
		case WM_PAINT:
			//������
			GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
			GUI_Clear();
			GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
			GUI_ClearRect(0, 296, 240, 320);
			GUI_SetColor(GUI_WHITE);
			GUI_DrawVLine(120, 296, 320);
			//д��
			GUI_SetFont(&GUI_FontHZ24);
			GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT1);
			GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
			GUI_DispStringAt("��Һ����", 5, 56);
			GUI_DispStringAt("��Һ����", 5, 126);
			GUI_DispStringAt("��Һʱ��", 5, 224);
			GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT2);
			GUI_DispStringAt("����", 150, 182);
			GUI_DispStringAt("ʣ��", 150, 236);
			GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT3);
			GUI_DispStringHCenterAt("00:16:26", 175, 206);
			GUI_DispStringHCenterAt("00:35:51", 175, 262);
			GUI_DispStringAt("20", 126, 56);//��Ҫ��һ�������
											//��ť����
			GUI_SetFont(&GUI_FontHZ16);
			GUI_SetColor(GUI_WHITE);
			GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
			GUI_DispStringHCenterAt("����", 60, 300);
			GUI_DispStringHCenterAt("ֹͣ", 180, 300);
		default:
			break;
	}
}
//void block(int display, int num, int x, int y) {
//	if (display != 0) {
//		switch (num)
//		{
//		case 1:
//			GUI_SetBkColor(GUI_GREEN);
//			GUI_DrawArc()
//
//		default:
//			break;
//		}
//	}else{
//		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
//	}
//}
