#include "mypage.h"
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
	WM_EnableMemdev(WM_HBKWIN); //启用储存设备
	W_pageShuyeSetting();
}
void W_pageDisplay(void) {
	WM_HWIN hWnd;
	GUI_PID_STATE touchState;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageDisplay, 0);
	GUI_Exec();
	while (1)
	{
		GUI_Delay(20);
	}
}
void W_pageHome(void) {
	WM_HWIN hWnd;
	LISTWHEEL_Handle a;
	char * apText[] = {
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday",
		"Sunday",
		NULL

	};
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageHome, 0);
	a = LISTWHEEL_CreateEx(10, 10, 50, 50, hWnd, WM_CF_SHOW, 0, 0, apText);

	GUI_Exec();
	while (1)
	{
		GUI_Delay(50);

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
		//GUI_PID_GetState(&touchState);
		//if (touchState.Pressed == 1) {
		//	while (touchState.Pressed == 1) {
		//		GUI_PID_GetState(&touchState);
		//	}
		//	if (touchState.y < 17.9&&touchState.x>191) {
		//		GUI_DispStringAt("0", 0, 0);
		//	}
		//	else if (touchState.y > 108 && touchState.y < 150) {
		//		GUI_DispStringAt("1", 0, 0);
		//	}
		//	else if (touchState.y >= 150 && touchState.y<193) {
		//		GUI_DispStringAt("2", 0, 0);
		//	}
		//	else if (touchState.y >= 193 && touchState.y <= 235) {
		//		GUI_DispStringAt("3", 0, 0);
		//	}
		//	else if (touchState.y >= 235 && touchState.y <= 278) {
		//		GUI_DispStringAt("4", 0, 0);
		//	}
		//	else if (touchState.y >= 278) {
		//		WM_DeleteWindow(hWnd);
		//		break;
		//	}
		//}
	}

}
void W_pageShuyeSetting(void) {
	WM_HWIN hWnd, hNumPad;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageShuyeSetting, 0);
	hNumPad = GUI_CreateDialogBox(_aDialogNumPad, GUI_COUNTOF(_aDialogNumPad), _cbDialogNumPad, hWnd, 0, 0); /* Create the numpad dialog */

	WM_SetStayOnTop(hNumPad, 1);
	createMultipage(&hWnd);
	GUI_Exec();
	while (1)
	{
		GUI_Delay(50);
		//GUI_PID_GetState(&touchState);
		//if (touchState.Pressed == 1) {
		//	while (touchState.Pressed == 1) {
		//		GUI_PID_GetState(&touchState);
		//	}
		//	if (touchState.y >= 296) {
		//		if (touchState.x < 120) {
		//			WM_DeleteWindow(hWnd);
		//			break;
		//		}
		//		else {
		//			W_pageDisplay();
		//		}
		//	}
		//}
	}

}
void pageShuyeSetting(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_Clear();

		//画框
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_CONTENT);
		GUI_ClearRect(0, 85, 240, 296);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_ClearRect(0, 296, 240, 320);
		//画线
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(85, 0, 240);
		GUI_DrawHLine(136, 0, 240);
		GUI_DrawHLine(187, 0, 240);
		GUI_DrawHLine(238, 0, 240);
		GUI_DrawHLine(295, 0, 240);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120, 296, 320);
		//写字
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
void pageHome(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_PAGEHOME_TITLE_BACKGROUND);
		GUI_Clear();

		//画框
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
		GUI_ClearRect(0, 197, 240, 259);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
		GUI_ClearRect(0, 259, 240, 320);

		//画线
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(197, 0, 240);
		GUI_DrawHLine(259, 0, 240);

		//写字
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
			if (pState->y < 259 && pState->y>197) {//输液设置
				WM_DeleteWindow(pMsg->hWin);
				W_pageShuyeSetting();
			}
			else if (pState->y > 259 && pState->y < 320) {//系统设置
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
		//画背景
		GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
		GUI_ClearRect(0, 109, 240, 320);
		//画线
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(109, 0, 240);
		GUI_DrawHLine(150, 0, 240);
		GUI_DrawHLine(193, 0, 240);
		GUI_DrawLine(0, 235, 240, 235);
		GUI_DrawHLine(278, 0, 240);
		//写字
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
		//画背景
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
		GUI_Clear();
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
		GUI_ClearRect(0, 296, 240, 320);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120, 296, 320);
		//写字
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
		GUI_DispStringAt("20", 126, 56);//需要大一点的字体
										//按钮字体
		GUI_SetFont(&GUI_Font16_1);
		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
		GUI_DispStringHCenterAt("BACK", 60, 300);
		GUI_DispStringHCenterAt("PAUSE", 180, 300);

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
	MULTIPAGE_Handle aMultipage;
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
		{ EDIT_CreateIndirect,      "time1",       GUI_ID_EDIT1,           50,  50,  40,  20, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "time2",       GUI_ID_EDIT2,           170,  50,  40,  20, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "speed1",       GUI_ID_EDIT3,           50,  85,  40,  20, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "speed2",       GUI_ID_EDIT4,           170,  85,  40,  20, EDIT_CF_HCENTER }
	};


	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);

	MULTIPAGE_SetSkinFlexProps(&multipage_skin_SELECTED, MULTIPAGE_SKINFLEX_PI_SELECTED);
	MULTIPAGE_SetSkinFlexProps(&multipage_skin_ENABLE, MULTIPAGE_SKINFLEX_PI_ENABLED);

	aMultipage = MULTIPAGE_CreateEx(0, 84, 240, 212, *hWnd, WM_CF_SHOW, 0, 0);
	MULTIPAGE_SetFont(aMultipage, &GUI_Font16B_1);
//	MULTIPAGE_SetSkin(aMultipage, _MultipageSkin);
//	MULTIPAGE_SetAlign(aMultipage, MULTIPAGE_ALIGN_BOTTOM | MULTIPAGE_ALIGN_LEFT); //左下方
//	MULTIPAGE_SetRotation(aMultipage, WIDGET_STATE_VERTICAL); //旋转
	//	pageBottle = GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), NULL, WM_UNATTACHED, 0, 0);
	//pageBottle = WM_CreateWindow(0, 0, 240, 212, WM_CF_SHOW, _cbBottle1, 0);
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     1      ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     2      ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     3      ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     4      ");

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
						Key = (int)'0';                        /* Get the text from the array */
					}
					GUI_SendKeyMsg(Key, Pressed);                                /* Send a key message to the focussed window */
				}
				break;
			}
		default:
			WM_DefaultProc(pMsg);
	}
}
void _cbBottle4(WM_MESSAGE *pMsg) {
	WM_HWIN hEdit;
	unsigned Id;
	int NCode;
	char s[5];
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
		break;
	case WM_INIT_DIALOG:
		for (int i = 0; i < 5; i++) {
			hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0 + i);
			if (!_pEditCallback) {
				_pEditCallback = WM_SetCallback(hEdit, _cbEdit); // Overwrite callback function and remember original function
			}
			else {
				WM_SetCallback(hEdit, _cbEdit);                  // Overwrite callback function
			}
			WIDGET_SetEffect(hEdit, &WIDGET_Effect_None);
			//EDIT_SetDecMode(hEdit,0,0,9999,1, GUI_EDIT_NORMAL);
		}
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
		NCode = pMsg->Data.v;                 /* Notification code */
		switch (NCode)
		{
		case WM_NOTIFICATION_VALUE_CHANGED:
			hEdit = WM_GetDialogItem(pMsg->hWin, Id);
			EDIT_GetText(hEdit, s, 5);
			hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
			EDIT_SetText(hEdit, s);
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
		timeText1 = EDIT_CreateEx(50, 50, 40, 20, pMsg->hWin, WM_CF_SHOW, 0, 0, 4);
		timeText2 = EDIT_CreateEx(170, 50, 40, 20, pMsg->hWin, WM_CF_SHOW, 0, 0, 4);
		speedText1 = EDIT_CreateEx(50, 85, 40, 20, pMsg->hWin, WM_CF_SHOW, 0, 0, 4);
		speedText2 = EDIT_CreateEx(170, 85, 40, 20, pMsg->hWin, WM_CF_SHOW, 0, 0, 4);
		//WIDGET_SetEffect(btext,&WIDGET_Effect_None);//取消边框
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
