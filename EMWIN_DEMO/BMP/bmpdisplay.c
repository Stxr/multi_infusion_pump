#include "bmpdisplay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103��Ӣ������
//STemwin BMPͼƬ��ʾ 
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/10
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif

static FIL BMPFile;
static char bmpBuffer[BMPPERLINESIZE];
/*******************************************************************
*
*       Static functions
*
********************************************************************
*/
/*********************************************************************
*
*       BmpGetData
*
* Function description
*   This routine is called by GUI_BMP_DrawEx(). The routine is responsible
*   for setting the data pointer to a valid data location with at least
*   one valid byte.
*
* Parameters:
*   p           - Pointer to application defined data.
*   NumBytesReq - Number of bytes requested.
*   ppData      - Pointer to data pointer. This pointer should be set to
*                 a valid location.
*   StartOfFile - If this flag is 1, the data pointer should be set to the
*                 beginning of the data stream.
*
* Return value:
*   Number of data bytes available.
*/
static int BmpGetData(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off) 
{
	static int readaddress=0;
	FIL * phFile;
	UINT NumBytesRead;
	#if SYSTEM_SUPPORT_UCOS
		OS_CPU_SR cpu_sr;
	#endif
	
	phFile = (FIL *)p;
	
	if (NumBytesReq > sizeof(bmpBuffer)) 
	{
		NumBytesReq = sizeof(bmpBuffer);
	}

	//�ƶ�ָ�뵽Ӧ�ö�ȡ��λ��
	if(Off == 1) readaddress = 0;
	else readaddress=Off;
	#if SYSTEM_SUPPORT_UCOS
		OS_ENTER_CRITICAL();	//�ٽ���
	#endif
	f_lseek(phFile,readaddress); 
	
	//��ȡ���ݵ���������
	f_read(phFile,bmpBuffer,NumBytesReq,&NumBytesRead);
	#if SYSTEM_SUPPORT_UCOS
		OS_EXIT_CRITICAL();	//�˳��ٽ��� 
	#endif
	*ppData = (U8 *)bmpBuffer;
	return NumBytesRead;//���ض�ȡ�����ֽ���
}

//��ָ��λ����ʾ������ص�RAM�е�BMPͼƬ(���ļ�ϵͳ֧�֣�����СRAM���Ƽ�ʹ�ô˷�����)
//BMPFileName:ͼƬ��SD�����������洢�豸�е�·��
//mode:��ʾģʽ
//		0 ��ָ��λ����ʾ���в���x,yȷ����ʾλ��
//		1 ��LCD�м���ʾͼƬ����ѡ���ģʽ��ʱ�����x,y��Ч��
//x:ͼƬ���Ͻ���LCD�е�x��λ��(������modeΪ1ʱ���˲�����Ч)
//y:ͼƬ���Ͻ���LCD�е�y��λ��(������modeΪ1ʱ���˲�����Ч)
//member:  ���ű����ķ�����
//denom:���ű����ķ�ĸ��
//����ֵ:0 ��ʾ����,���� ʧ��
int dispbmpex(u8 *BMPFileName,u8 mode,u32 x,u32 y,int member,int denom)
{
	char result;
	int XSize,YSize;
	float Xflag,Yflag;
	GUI_COLOR forecolor,bkcolor;
	forecolor=GUI_GetColor();			//��ȡ��ǰǰ��ɫ
	bkcolor=GUI_GetBkColor();			//��ȡ��ǰ����ɫ
	
	result = f_open(&BMPFile,(const TCHAR*)BMPFileName,FA_READ);	//���ļ�
	//�ļ��򿪴���
	if(result != FR_OK) 	return 1;
		
	switch(mode)
	{
		case 0:	//��ָ��λ����ʾͼƬ
			if((member == 1) && (denom == 1)) //�������ţ�ֱ�ӻ���
			{
				GUI_BMP_DrawEx(BmpGetData,&BMPFile,x,y);//��ָ��λ����ʾBMPͼƬ
			}else //����ͼƬ��Ҫ����
			{
				GUI_BMP_DrawScaledEx(BmpGetData,&BMPFile,x,y,member,denom);
			}
			break;
		case 1:	//��LCD�м���ʾͼƬ
			XSize = GUI_BMP_GetXSizeEx(BmpGetData,&BMPFile);	//��ȡͼƬ��X���С
			YSize = GUI_BMP_GetYSizeEx(BmpGetData,&BMPFile);	//��ȡͼƬ��Y���С
			if((member == 1) && (denom == 1)) //�������ţ�ֱ�ӻ���
			{
				//��LCD�м���ʾͼƬ
				GUI_BMP_DrawEx(BmpGetData,&BMPFile,(lcddev.width-XSize)/2-1,(lcddev.height-YSize)/2-1);
			}else //����ͼƬ��Ҫ����
			{
				Xflag = (float)XSize*((float)member/(float)denom);
				Yflag = (float)YSize*((float)member/(float)denom);
				XSize = (lcddev.width-(int)Xflag)/2-1;
				YSize = (lcddev.height-(int)Yflag)/2-1;
				GUI_BMP_DrawScaledEx(BmpGetData,&BMPFile,XSize,YSize,member,denom);
			}
			break;
	}
	f_close(&BMPFile);		//�ر�BMPFile�ļ�
	GUI_SetColor(forecolor);		//�ָ�ǰ��ɫ
	GUI_SetBkColor(bkcolor);		//�ָ�����ɫ
	return 0;
}

//�˺�����GUI_BMP_Serialize()���ã��������ļ�д���ֽ�
static void _WriteByte2File(U8 Data, void * p) 
{
	UINT nWritten;
	f_write((FIL*)p,&Data,1,&nWritten);
}

//����һ��BMPͼƬ�����浽SD����,ʵ����Ļ��ͼ���ܣ�
//*filepath:�ļ�·��
//x0:����BMP�ļ���X��ʼλ��
//y0:����BMP�ļ���Y��ʼλ��
//Xsize:X�Ĵ�С
//Ysize:Y�Ĵ�С
void create_bmppicture(u8 *filename,int x0,int y0,int Xsize,int Ysize)
{
	static FIL hFile;
	GUI_COLOR forecolor,bkcolor;
	forecolor=GUI_GetColor();		//��ȡ��ǰǰ��ɫ
	bkcolor=GUI_GetBkColor();		//��ȡ��ǰ����ɫ
	//����һ���ļ���·��Ϊfilename,����ļ�ԭ���ʹ��ڵĻ��ᱻ�½����ļ����ǵ���
	f_open(&hFile,(const TCHAR*)filename,FA_READ|FA_WRITE|FA_CREATE_ALWAYS);
	GUI_BMP_SerializeEx(_WriteByte2File,x0,y0,Xsize,Ysize,&hFile);
	f_close(&hFile);	//�ر��ļ�
	GUI_SetColor(forecolor);		//�ָ�ǰ��ɫ
	GUI_SetBkColor(bkcolor);		//�ָ�����ɫ
}	

void bmpdisplay_demo(void)
{
	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_FontHZ16);
	GUI_Clear();
	
	while(1)
	{
		GUI_DispStringHCenterAt("��ָ��λ����ʾһ��������ص�BMPͼƬ",0,0);
		dispbmpex("1:/SYSTEM/SYSICO/ebook.bmp",1,20,	20,	1,1);
		GUI_Delay(1000);
		GUI_Clear();
	
	
//		GUI_DispStringHCenterAt("��LCD�м���ʾһ����С1/2��������ص�BMPͼƬ",400,5);
//		dispbmpex("0:/PICTURE/BMP/ALIENTEKLOGO.bmp",1,0,	0,	1,2);
//		GUI_Delay(1000);
//		GUI_Clear();
//	
//		GUI_DispStringHCenterAt("��LCD�м���ʾһ������4/3����������ص�BMPͼƬ",400,5);
//		dispbmpex("0:/PICTURE/BMP/ALIENTEKLOGO.bmp",1,0,	0,	4,3);
//		GUI_Delay(1000);
//		GUI_Clear();
	}
}
