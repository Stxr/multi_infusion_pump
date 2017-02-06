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
#include "fontupd.h"
#include "exfuns.h"
#include "includes.h"
#include "bitmapdisplay.h"
#include "bmpdisplay.h"
#include "WM.h"
#include "DIALOG.h"
#include "usmart.h"
#include "image2lcd.h"
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

#define MULTIPAGE_PI_ENABLED MULTIPAGE_SKINFLEX_PI_ENABLED

//窗口句柄
static WM_HWIN _hWindow1;  	//窗口1
static WM_HWIN _hWindow2;	//窗口2
static WM_HWIN _hChild1;		//子窗口1
static WM_CALLBACK * _pEditCallback;
void pageSetting(WM_MESSAGE *pMsg);
void pageHome(WM_MESSAGE *pMsg);
void pageShuyeSetting(WM_MESSAGE *pMsg);
void pageDisplay(WM_MESSAGE *pMsg);
void _cbBottle1(WM_MESSAGE *pMsg);
void _cbBottle4(WM_MESSAGE *pMsg);
void _cbDialogNumPad(WM_MESSAGE *pMsg);
void _cbEdit(WM_MESSAGE * pMsg);
void _cbEditAddKey(EDIT_Handle hObj, int Key);
void W_pageHome(void);
void W_pageShuyeSetting(void);
void W_pageSetting(void);
void W_pageDisplay(void);
void test_multipage(void);
void createMultipage(HBWIN *);
void _MultipageSkin(WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
void _mCreatSpinBox(int x0, int y0, int xSize, int ySize, GUI_HWIN hParent, int WinFlags, int Id, int Min, int Max);
