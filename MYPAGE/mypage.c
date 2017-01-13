#include "mypage.h"
void pageShuyeSetting() {
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
	GUI_SetFont(&GUI_FontHZ24);
	GUI_DispStringHCenterAt("PRE-SETTING", 120, 40);

	GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT1);
	GUI_SetBkColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontHZ16);
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
	GUI_SetFont(&GUI_FontHZ16);
	GUI_DispStringAt("valume:        ml", 85, 90);
	GUI_DispStringAt("time:            ", 85, 110);//delt=20
	GUI_DispStringAt("valume:        ml", 85, 140);
	GUI_DispStringAt("time:            ", 85, 160);//delt=20
	GUI_DispStringAt("valume:        ml", 85, 193);
	GUI_DispStringAt("time:            ", 85, 213);//delt=20
	GUI_DispStringAt("valume:        ml", 85, 243);
	GUI_DispStringAt("time:            ", 85, 263);//delt=20
	GUI_PID_STATE touchState;
	while (1)
	{
		GUI_PID_GetState(&touchState);
    if(touchState.Pressed==1){
      if (touchState.y >= 296) {
        if (touchState.x < 120) {
          break; //回到主页
        }
      }
    }
	}
}
void pageHome() {
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
	GUI_SetFont(&GUI_FontHZ24);
	GUI_DispStringHCenterAt("MULTI-quanzid", 120, 70);
	GUI_DispStringHCenterAt("zhinegnshuyebao", 120, 100);

	GUI_SetColor(MYCOLOR_PAGEHOME_SETTING_TEXT);
	GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
	GUI_SetFont(&GUI_FontHZ16);
	GUI_DispStringHCenterAt("shuyeshezhi", 120, 218);
	GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
	GUI_DispStringHCenterAt("zhinegnshuyebao", 120, 280);
	GUI_PID_STATE touchState;
	GUI_SetColor(MYCOLOR_TITLE_TEXT);
	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
	while (1)
	{
		GUI_PID_GetState(&touchState);
    if(touchState.Pressed==1){
      if (touchState.y < 259&&touchState.y>197) {//输液设置
        pageShuyeSetting();
      }
      else if (touchState.y > 259 && touchState.y < 320) {//系统设置
        //GUI_DispStringAt("1", 0, 0);
        pageSetting();
      }
    }
	}
}
void pageSetting(void) {
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

	GUI_PID_STATE touchState;
	GUI_SetColor(MYCOLOR_TITLE_TEXT);
	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
	while (1)
	{
		GUI_PID_GetState(&touchState);
    if(touchState.Pressed==1){
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
        break;
      }
    }
	}
}
