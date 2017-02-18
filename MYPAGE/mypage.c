#include "mypage.h"
double shuyeData[4][5];
char s[5];
int my_index=0;
double data[5];
MULTIPAGE_Handle aMultipage;
static const GUI_WIDGET_CREATE_INFO _aDialogNumPad[] = {
	//
	//  Function                 Text      Id					 Px   Py   Dx   Dy
	//
	{ WINDOW_CreateIndirect,   0,        0,						 0,	 217, 240,  78 },
	{ BUTTON_CreateIndirect,   "7",      GUI_ID_USER + 7,		 0,  0,  60,  26 },
	{ BUTTON_CreateIndirect,   "8",      GUI_ID_USER + 8,		60,  0,  60,  26},
	{ BUTTON_CreateIndirect,   "9",      GUI_ID_USER + 9,	   120,  0,  60,  26},
	{ BUTTON_CreateIndirect,   "4",      GUI_ID_USER + 4,		 0,	 26,  60,  26},
	{ BUTTON_CreateIndirect,   "5",      GUI_ID_USER + 5,		60,	 26,  60,  26},
	{ BUTTON_CreateIndirect,   "6",      GUI_ID_USER + 6,	   120,  26,  60,  26},
	{ BUTTON_CreateIndirect,   "1",      GUI_ID_USER + 1,		 0,	 52,  60,  26},
	{ BUTTON_CreateIndirect,   "2",      GUI_ID_USER + 2,		60,	 52,  60,  26},
	{ BUTTON_CreateIndirect,   "3",      GUI_ID_USER + 3,		120, 52,  60,  26},
	{ BUTTON_CreateIndirect,   "Del",    GUI_ID_USER + 11,		180, 0,  60,  26},
	{ BUTTON_CreateIndirect,   "0",      GUI_ID_USER + 0,		180, 26,  60,  26},
	{ BUTTON_CreateIndirect,   ".",      GUI_ID_USER + 10,		180, 52,  60,  26},
};


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
void MainTask(void) {
	GUI_Init();
	WM_EnableMemdev(WM_HBKWIN); //??????
	W_pageShuyeDisplay();
	while (1) {
		GUI_Delay(500);
	}
}
void W_pageDisplay(void) {
	WM_HWIN hWnd;
	my_index = 0;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageDisplay, 0);
	GUI_Exec();
	//while (1)
	//{
	//	GUI_Delay(20);
	//}
}
void W_pageHome(void) {
	WM_HWIN hWnd;
	//LISTWHEEL_Handle a;
	//char * apText[] = {
	//	"Monday",
	//	"Tuesday",
	//	"Wednesday",
	//	"Thursday",
	//	"Friday",
	//	"Saturday",
	//	"Sunday",
	//	NULL

	//};
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageHome, 0);
	//a = LISTWHEEL_CreateEx(10, 10, 50, 50, hWnd, WM_CF_SHOW, 0, 0, apText);

	GUI_Exec();
	//while (1)
	//{
	//	GUI_Delay(50);

	//}
}
void W_pageSetting(void) {
	WM_HWIN hWnd;
	GUI_PID_STATE touchState;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageSetting, 0);
	GUI_Exec();
	GUI_SetColor(MYCOLOR_TITLE_TEXT);
	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
	//while (1)
	//{
	//	GUI_Delay(20);
	//}

}
void W_pageShuyeSetting(void) {
	WM_HWIN hWnd, hNumPad;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageShuyeSetting, 0);
	hNumPad = GUI_CreateDialogBox(_aDialogNumPad, GUI_COUNTOF(_aDialogNumPad), _cbDialogNumPad, hWnd, 0, 0); /* Create the numpad dialog */
	WM_SetStayOnTop(hNumPad, 1);
	createMultipage(&hWnd);
	//while (1)
	//{
	//	GUI_Delay(50);
	//
	//}

}
void W_pageShuyeDisplay(void) {
	WM_HWIN hWnd;
	my_index=0;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageShuyeDisplay, 0);
}
void pageShuyeDisplay(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	GUI_HWIN hItem;
	char tempt[20];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_Clear();

		//??
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_CONTENT);
		GUI_ClearRect(0, 60.8, 240, 296);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_ClearRect(0, 296, 240, 320);
		//??
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(60.8, 0, 240);
		GUI_DrawHLine(119.2, 0, 240);
		GUI_DrawHLine(177.6, 0, 240);
		GUI_DrawHLine(236, 0, 240);
		GUI_DrawHLine(295, 0, 240);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120, 296, 320);
		//??
		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_Font24_1);
		GUI_DispStringAt("PRE-SETTING", 72, 23.4);

		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT1);
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringAt("ONE", 12.4, 60.8+20.4);
		GUI_DispStringAt("TWO", 12.4, 119.2+20.4);
		GUI_DispStringAt("THREE", 12.4, 177.6+20.4);
		GUI_DispStringAt("FOUR", 12.4, 236+20.4);

		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_DispStringHCenterAt("BACK", 60, 300);
		GUI_DispStringHCenterAt("CONFIRM", 180, 300);

		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetFont(&GUI_Font13_1);
		sprintf(tempt, "valume: %.1f ml", shuyeData[0][0]);
		GUI_DispStringAt(tempt, 110, 60.8 + 4.8);
		sprintf(tempt, "valume: %.1f ml", shuyeData[1][0]);
		GUI_DispStringAt(tempt, 110, 119.2 + 4.8);
		sprintf(tempt, "valume: %.1f ml", shuyeData[2][0]);
		GUI_DispStringAt(tempt, 110, 177.6 + 4.8);
		sprintf(tempt, "valume: %.1f ml", shuyeData[3][0]);
		GUI_DispStringAt(tempt, 110, 236 + 4.8);

		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[0][1]);
		GUI_DispStringAt(tempt,    90.4, 60.8 + 22);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[1][1]);
		GUI_DispStringAt(tempt, 90.4, 119.2+ 22);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[2][1]);
		GUI_DispStringAt(tempt, 90.4, 177.6+ 22);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[3][1]);
		GUI_DispStringAt(tempt, 90.4, 236+ 22);

		sprintf(tempt, "time: %.1f min", shuyeData[0][3]);
		GUI_DispStringAt(tempt, 90.4, 60.8 + 40.8);
		sprintf(tempt, "time: %.1f min", shuyeData[1][3]);
		GUI_DispStringAt(tempt, 90.4, 119.2 + 40.8);
		sprintf(tempt, "time: %.1f min", shuyeData[2][3]);
		GUI_DispStringAt(tempt, 90.4, 177.6 + 40.8);
		sprintf(tempt, "time: %.1f min", shuyeData[3][3]);
		GUI_DispStringAt(tempt, 90.4, 236 + 40.8);

		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[0][2]);
		GUI_DispStringAt(tempt, 172.8, 60.8 + 22);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[1][2]);
		GUI_DispStringAt(tempt, 172.8, 119.2 + 22);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[2][2]);
		GUI_DispStringAt(tempt, 172.8, 177.6 + 22);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[3][2]);
		GUI_DispStringAt(tempt, 172.8, 236 + 22);

		sprintf(tempt, "time: %.1f min", shuyeData[0][4]);
		GUI_DispStringAt(tempt, 172.8, 60.8 + 40.8);
		sprintf(tempt, "time: %.1f min", shuyeData[1][4]);
		GUI_DispStringAt(tempt, 172.8, 119.2 + 40.8);
		sprintf(tempt, "time: %.1f min", shuyeData[2][4]);
		GUI_DispStringAt(tempt, 172.8, 177.6 + 40.8);
		sprintf(tempt, "time: %.1f min", shuyeData[3][4]);
		GUI_DispStringAt(tempt, 172.8, 236 + 40.8);

	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y >= 296) {
				if (pState->x < 120) {
					WM_DeleteWindow(pMsg->hWin);
					W_pageShuyeSetting();
				}
				else {
					WM_DeleteWindow(pMsg->hWin);
					W_pageDisplay();
				}
			}
		}
		break;
	default:
		break;
	}
}
void pageShuyeSetting(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	GUI_HWIN hItem;
//	double shuyeData[4][5];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_Clear();

		//??
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_CONTENT);
		GUI_ClearRect(0, 85, 240, 296);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_ClearRect(0, 296, 240, 320);
		//??
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(85, 0, 240);
		GUI_DrawHLine(136, 0, 240);
		GUI_DrawHLine(187, 0, 240);
		GUI_DrawHLine(238, 0, 240);
		GUI_DrawHLine(295, 0, 240);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120, 296, 320);
		//??
		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_Font24_1);
		GUI_DispStringHCenterAt("PRE-SETTING", 120, 40);

		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT1);
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringHCenterAt("ONE", 36, 105);
		GUI_DispStringHCenterAt("TWO", 36, 156);
		GUI_DispStringHCenterAt("THREE", 36, 207);
		GUI_DispStringHCenterAt("FOUR", 36, 258);

		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_DispStringHCenterAt("BACK", 60, 300);
		GUI_DispStringHCenterAt("CONFIRM", 180, 300);

		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringAt("valume:        ml", 85, 90);
		GUI_DispStringAt("time:            ", 85, 110);//delt=20
		GUI_DispStringAt("valume:        ml", 85, 140);
		GUI_DispStringAt("time:            ", 85, 160);//delt=20
		GUI_DispStringAt("valume:        ml", 85, 193);
		GUI_DispStringAt("time:            ", 85, 213);//delt=20
		GUI_DispStringAt("valume:        ml", 85, 243);
		GUI_DispStringAt("time:            ", 85, 263);//delt=20



	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y >= 296) {
				if (pState->x < 120) {
					WM_DeleteWindow(pMsg->hWin);
					W_pageHome();
				}
				else {
					//save the data
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 5; j++) {
							hItem = WM_GetDialogItem(MULTIPAGE_GetWindow(aMultipage, i), GUI_ID_EDIT0+j);
							EDIT_GetText(hItem, s, 4);
							sscanf(s, "%lf", &shuyeData[i][j]);
						}
					}
					WM_DeleteWindow(pMsg->hWin);
					W_pageShuyeDisplay();
				}
			}
		}
		break;
	default:
		break;
	}
}
void pageHome(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_PAGEHOME_TITLE_BACKGROUND);
		GUI_Clear();

		//??
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
		GUI_ClearRect(0, 197, 240, 259);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
		GUI_ClearRect(0, 259, 240, 320);

		//??
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(197, 0, 240);
		GUI_DrawHLine(259, 0, 240);

		//??
		GUI_SetColor(MYCOLOR_PAGEHOME_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_Font24_1);
		GUI_DispStringHCenterAt("MULTI-quanzid", 120, 70);
		GUI_DispStringHCenterAt("zhinegnshuyebao", 120, 100);

		GUI_SetColor(MYCOLOR_PAGEHOME_SETTING_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringHCenterAt("shuyeshezhi", 120, 218);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
		GUI_DispStringHCenterAt("zhinegnshuyebao", 120, 280);
		break;
	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y < 259 && pState->y>197) {//????
				WM_DeleteWindow(pMsg->hWin);
				W_pageShuyeSetting();
			}
			else if (pState->y > 259 && pState->y < 320) {//????
														  //GUI_DispStringAt("1", 0, 0);
				WM_DeleteWindow(pMsg->hWin);
				W_pageSetting();
			}
		}
		break;
	default:
		break;
	}
}
void pageSetting(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
		GUI_Clear();
		GUI_SetFont(&GUI_Font32_ASCII);
		//GUI_DispString("hello,emwin");
		//???
		GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
		GUI_ClearRect(0, 109, 240, 320);
		//??
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(109, 0, 240);
		GUI_DrawHLine(150, 0, 240);
		GUI_DrawHLine(193, 0, 240);
		GUI_DrawLine(0, 235, 240, 235);
		GUI_DrawHLine(278, 0, 240);
		//??
		GUI_SetColor(MYCOLOR_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_Font20_1);
		GUI_DispStringHCenterAt("System Setting", 120, 51.6);

		GUI_SetColor(MYCOLOR_CONTENT_TEXT);
		GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
		GUI_SetFont(&GUI_Font16B_1);
		GUI_DispStringHCenterAt("Personal Setting", 120, 108 + 10);
		GUI_DispStringHCenterAt("System Update", 120, 150.4 + 10);
		GUI_DispStringHCenterAt("System Statistics", 120, 192.8 + 10);
		GUI_DispStringHCenterAt("About", 120, 235.2 + 10);
		GUI_DispStringHCenterAt("Back", 120, 277.6 + 10);

	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y < 17.9&&pState->x>191) {
				GUI_DispStringAt("0", 0, 0);
			}
			else if (pState->y > 108 && pState->y < 150) {
				GUI_DispStringAt("1", 0, 0);
			}
			else if (pState->y >= 150 && pState->y<193) {
				GUI_DispStringAt("2", 0, 0);
			}
			else if (pState->y >= 193 && pState->y <= 235) {
				GUI_DispStringAt("3", 0, 0);
			}
			else if (pState->y >= 235 && pState->y <= 278) {
				GUI_DispStringAt("4", 0, 0);
			}
			else if (pState->y >= 278) {
				WM_DeleteWindow(pMsg->hWin);
				W_pageHome();
			}
		}
		break;
	default:
		break;
	}

}
void pageDisplay(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		//???
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
		GUI_Clear();
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
		GUI_ClearRect(0, 296, 240, 320);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120, 296, 320);
		//??
		GUI_SetFont(&GUI_Font24_1);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT1);
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
		GUI_DispStringAt("shuyesulv", 5, 56);
		GUI_DispStringAt("shuyeshul", 5, 126);
		GUI_DispStringAt("shuyeTime", 5, 224);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT2);
		GUI_DispStringAt("Used", 150, 182);
		GUI_DispStringAt("Left", 150, 236);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT3);
		GUI_DispStringHCenterAt("00:16:26", 175, 206);
		GUI_DispStringHCenterAt("00:35:51", 175, 262);
		GUI_DispStringAt("20", 126, 56);//????????
										//????
		GUI_SetFont(&GUI_Font16_1);
		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
		GUI_DispStringHCenterAt("BACK", 60, 300);
		GUI_DispStringHCenterAt("PAUSE", 180, 300);

		//display
//		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 5; j++) {
//				GUI_DispDecAt(shuyeData[i][j], 30*j, 30*i, 3);
//			}
//		}


	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y >= 296) {
				if (pState->x < 120) {
					WM_DeleteWindow(pMsg->hWin);
					W_pageShuyeSetting();
				}
				else
				{

				}
			}
		}
		break;
	default:
		break;
	}
}
void createMultipage(WM_HWIN *hWnd) {
	WM_HWIN pageBottle, hNumPad;

	MULTIPAGE_SKINFLEX_PROPS multipage_skin_SELECTED = {
		GUI_WHITE,{ GUI_WHITE,GUI_WHITE },{ GUI_WHITE ,GUI_WHITE },0Xe3d7d4,GUI_BLACK
	};
	MULTIPAGE_SKINFLEX_PROPS multipage_skin_ENABLE = {
		GUI_YELLOW,{ MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND,MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND },
		{ MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND ,MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND },
		MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND,GUI_BLACK
	};
	GUI_WIDGET_CREATE_INFO _aDialogCreate4[] = {
		{ WINDOW_CreateIndirect,    "Dialog 4",               0,            0,   0, 240, 212, FRAMEWIN_CF_MOVEABLE },
		{ EDIT_CreateIndirect,		"bottle1",     GUI_ID_EDIT0,           90,  16,  40,  20, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "speed1",       GUI_ID_EDIT1,           50,  50,  40,  20, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "speed2",       GUI_ID_EDIT2,           170,  50,  40,  20, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "time1",       GUI_ID_EDIT3,           50,  85,  40,  20, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "time2",       GUI_ID_EDIT4,           170,  85,  40,  20, EDIT_CF_HCENTER }
	};

	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);

	MULTIPAGE_SetSkinFlexProps(&multipage_skin_SELECTED, MULTIPAGE_SKINFLEX_PI_SELECTED);
	MULTIPAGE_SetSkinFlexProps(&multipage_skin_ENABLE, MULTIPAGE_SKINFLEX_PI_ENABLED);

	aMultipage = MULTIPAGE_CreateEx(0, 84, 240, 212, *hWnd, WM_CF_SHOW, 0, 0);
	MULTIPAGE_SetFont(aMultipage, &GUI_Font16B_1);
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     1      ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     2      ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     3      ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     4      ");
	MULTIPAGE_SelectPage(aMultipage, 0);

}
void _cbBottle4(WM_MESSAGE *pMsg) {
	WM_HWIN hEdit, hEdit1;
	unsigned Id;
	int NCode;
	char buff[5],c_valume[4];
	char sDest[10];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(GUI_WHITE);
		GUI_Clear();
		GUI_SetFont(&GUI_Font20_1);
		GUI_SetColor(GUI_BLACK);
		GUI_DispStringAt("bottle1:", 16, 16);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringAt("ML", 130, 16);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringAt("speed1:", 5, 50);
		GUI_DispStringAt("ml/s", 90, 50);
		GUI_DispStringAt("time1:", 5, 85);
		GUI_DispStringAt("min", 90, 85);
		GUI_DispStringAt("speed2:", 125, 50);
		GUI_DispStringAt("ml/s", 210, 50);
		GUI_DispStringAt("time2:", 125, 85);
		GUI_DispStringAt("min", 210, 85);
		break;
	case WM_INIT_DIALOG:
		my_index++;
		for (int i = 0; i < 5; i++) {
			hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0 + i);
			EDIT_SetMaxLen(hEdit, 4);
			WIDGET_SetEffect(hEdit, &WIDGET_Effect_None);

			//if (!_pEditCallback) {
			//	_pEditCallback = WM_SetCallback(hEdit, _cbEdit); // Overwrite callback function and remember original function
			//}
			//else {
			//	WM_SetCallback(hEdit, _cbEdit);                  // Overwrite callback function
			//}
			//EDIT_SetDecMode(hEdit,0,0,9999,1, GUI_EDIT_NORMAL);

			//初始化数据
			if (shuyeData[my_index - 1][i] != 0) {
				sprintf(buff, "%.1f", shuyeData[my_index - 1][i]);
			}
			else {
				sprintf(buff, "\0", shuyeData[my_index - 1][i]);
			}
			EDIT_SetText(hEdit, buff);
		}
		MULTIPAGE_GetSelection(aMultipage);
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
		NCode = pMsg->Data.v;                 /* Notification code */
		switch (NCode)
		{
		case WM_NOTIFICATION_VALUE_CHANGED:
			hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
			EDIT_GetText(hEdit1, c_valume, 4);
			sscanf(c_valume, "%lf", &data[0]);
			for (int i = 0; i < 5; i++) {   // save the data to data[5]
				hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0+i);
				EDIT_GetText(hEdit, buff, 5);
				sscanf(buff, "%lf", &data[i]);
			}
			switch (Id)
			{
			case GUI_ID_EDIT0:
				data[1] = data[2] = data[3] = data[4] = 0;
				break;
			case GUI_ID_EDIT1:
				hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
				if (data[1] != 0) {
					data[3] = data[0] / data[1];
					sprintf(buff, "%.1f", data[3]);
				}
				else {
					sprintf(buff, "%s", "err");
				}
				EDIT_SetText(hEdit1, buff);
				//break;
			case GUI_ID_EDIT3:
				data[2] = 5;
				if (data[3] * data[1] > data[0]) {
					data[3] = data[0] / data[1];
					hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
					sprintf(buff, "%.1f", data[3]);
					EDIT_SetText(hEdit1, buff);
				}
			case GUI_ID_EDIT2:
				if (data[0] - data[1] * data[3] <= 0) {
					data[4] = 0;
					data[2] = 0;
					//data[1] = data[0] / data[3];
				}
				else {
					data[4] = (data[0] - data[1] * data[3]) / data[2];
				}
				//hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
				//sprintf(buff, "%.1f", data[1]);
				//EDIT_SetText(hEdit1, buff);
				hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2);
				sprintf(buff, "%.1f", data[2]);
				EDIT_SetText(hEdit1, buff);
				hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT4);
				sprintf(buff, "%.1f", data[4]);
				EDIT_SetText(hEdit1, buff);
				//break;


			default:

				break;
			}
			//EDIT_GetText(hEdit, s, 5);
			//my_index = MULTIPAGE_GetSelection(aMultipage);

			//sprintf(sDest,"%d",my_index);
			//hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
			//EDIT_SetText(hEdit, sDest);

			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}
void _cbDialogNumPad(WM_MESSAGE * pMsg) {
	unsigned i;
	int      NCode;
	unsigned Id;
	int      Pressed;
	WM_HWIN  hDlg;
	WM_HWIN  hItem;
	//int _aKey[] = { GUI_KEY_BACKSPACE, GUI_KEY_TAB, GUI_KEY_LEFT, GUI_KEY_RIGHT };
	Pressed = 0;

	switch (pMsg->MsgId) {
		case WM_PAINT:
			break;
		case WM_INIT_DIALOG:
			for (i = 0; i < GUI_COUNTOF(_aDialogNumPad) - 1; i++) {
				hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_USER + i);
				BUTTON_SetFocussable(hItem, 0);		//Set all buttons non focussable
			}
			break;
		case WM_NOTIFY_PARENT:
			Id = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				Pressed = 1;
			case WM_NOTIFICATION_RELEASED:
				if ((Id >= GUI_ID_USER) && (Id <= (GUI_ID_USER + GUI_COUNTOF(_aDialogNumPad) - 1))) {
					int Key;
					if (Id < GUI_ID_USER + 11) {
						char acBuffer[10];
						BUTTON_GetText(pMsg->hWinSrc, acBuffer, sizeof(acBuffer)); /* Get the text of the button */
						Key = acBuffer[0];
					}
					else {
						//Key = _aKey[Id - GUI_ID_USER - 11];
						Key = GUI_KEY_BACKSPACE;                        /* Get the text from the array */
					}
					GUI_SendKeyMsg(Key, Pressed);                                /* Send a key message to the focussed window */
				}
				break;
			}
		default:
			WM_DefaultProc(pMsg);
	}
}
void _cbEditAddKey(EDIT_Handle hObj, int Key) {
	char acBuffer[2] = { 0 };

	switch (Key) {
	case GUI_KEY_LEFT:
		EDIT_SetpfAddKeyEx(hObj, 0);                            // Clear user defined AddKey function
		EDIT_SetCursorAtChar(hObj, EDIT_GetNumChars(hObj) - 1); // Set cursor if GUI_KEY_LEFT has been pressed
		break;
	case GUI_KEY_RIGHT:
		EDIT_SetpfAddKeyEx(hObj, 0);                            // Clear user defined AddKey function
		EDIT_SetCursorAtChar(hObj, 1);                          // Set cursor if GUI_KEY_RIGHT has been pressed
		break;
	case GUI_KEY_UP:                                          // Do not react on GUI_KEY_UP and GUI_KEY_DOWN
	case GUI_KEY_DOWN:
		break;
	default:
		if (Key >= 0x20) {
			acBuffer[0] = (U8)Key;
			EDIT_SetpfAddKeyEx(hObj, 0);                          // Clear user defined AddKey function
			EDIT_SetText(hObj, acBuffer);                         // Overwrite contents of edit widget with pressed key
		}
	}
}

void _cbEdit(WM_MESSAGE * pMsg) {
	switch (pMsg->MsgId) {
	case WM_PID_STATE_CHANGED:
		if (((const WM_PID_STATE_CHANGED_INFO*)pMsg->Data.p)->State) {
			return;            // Do not call edit callback
		}
		break;
	case WM_TOUCH:
		if (pMsg->Data.p) {  // Something happened in our area (pressed or released)
			const GUI_PID_STATE* pState;
			pState = (const GUI_PID_STATE*)pMsg->Data.p;
			if (pState->Pressed) {
				if (WM_GetFocussedWindow() != pMsg->hWin) {
					WM_SetFocus(pMsg->hWin);
					return;        // Do not call edit callback
				}
			}
		}
		break;
	case WM_SET_FOCUS:
		if (pMsg->Data.v == 1) {
			EDIT_SetpfAddKeyEx(pMsg->hWin, _cbEditAddKey); // Set function pointer for a user defined AddKey function
			EDIT_SetSel(pMsg->hWin, 0, -1);                // Select the whole contents of the edit field
		}
	}
	if (_pEditCallback) {
		_pEditCallback(pMsg);
	}
}

void _cbBottle1(WM_MESSAGE *pMsg) {
	EDIT_Handle btext,timeText1,timeText2,speedText1,speedText2;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(GUI_WHITE);
		GUI_Clear();
		GUI_SetFont(&GUI_Font20_1);
		GUI_SetColor(GUI_BLACK);
		GUI_DispStringAt("bottle1:", 16, 16);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringAt("ML", 130, 16);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringAt("time1:", 5, 50);
		GUI_DispStringAt("min", 90, 50);
		GUI_DispStringAt("speed:", 5, 85);
		GUI_DispStringAt("ml/s", 90, 85);
		GUI_DispStringAt("time2:", 125, 50);
		GUI_DispStringAt("min", 210, 50);
		GUI_DispStringAt("speed:", 125, 85);
		GUI_DispStringAt("ml/s", 210, 85);
		btext=EDIT_CreateEx(90, 16, 40, 20, pMsg->hWin, WM_CF_SHOW, 0, 0, 4);
		EDIT_CreateEx(50, 50, 40, 20, pMsg->hWin, WM_CF_SHOW, 0, 0, 4);
		EDIT_CreateEx(170, 50, 40, 20, pMsg->hWin, WM_CF_SHOW, 0, 0, 4);
		EDIT_CreateEx(50, 85, 40, 20, pMsg->hWin, WM_CF_SHOW, 0, 0, 4);
		EDIT_CreateEx(170, 85, 40, 20, pMsg->hWin, WM_CF_SHOW, 0, 0, 4);
		//WIDGET_SetEffect(btext,&WIDGET_Effect_None);//????
		//_mCreatSpinBox(90,10,70,20,pMsg->hWin, WM_CF_SHOW,0,0,999);
		//SPINBOX_SetFont(sbxCubage, &GUI_Font13HB_1);

		break;

	default:
		WM_DefaultProc(pMsg);
	}
}

void _MultipageSkin(WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {

	switch (pDrawItemInfo->Cmd) {
	//case WIDGET_ITEM_DRAW_BACKGROUND:
	//	GUI_SetBkColor(GUI_BLUE);
	//	//GUI_Clear();
	//	break;
	case WIDGET_ITEM_DRAW_FRAME:
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_Clear();
		break;
	default:
		break;

	}
}
void _mCreatSpinBox(int x0,int y0,int xSize,int ySize,GUI_HWIN hParent,int WinFlags,int Id,int Min,int Max) {
	SPINBOX_Handle sbxCubage;
	sbxCubage = SPINBOX_CreateEx(x0,y0,xSize,ySize,hParent,WinFlags,Id,Min,Max);
	SPINBOX_SetFont(sbxCubage, &GUI_Font13HB_1);
	SPINBOX_SetEdge(sbxCubage, SPINBOX_EDGE_CENTER);

}
void test_multipage(void) {

}
