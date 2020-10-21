#ifndef __AS608_H
#define __AS608_H
#include <stdio.h>
//#include "stm32f4xx.h"  


typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

#define PS_Sta   PAin(6)//��ָ��ģ��״̬����
#define CharBuffer1 0x01
#define CharBuffer2 0x02
#define CharBuffer3 0x03

extern u32 AS608Addr;//ģ���ַ

typedef struct  
{
	u16 pageID;//ָ��ID
	u16 mathscore;//ƥ��÷�
}SearchResult;

typedef struct
{
	u16 PS_max;//ָ���������
	u8  PS_level;//��ȫ�ȼ�
	u32 PS_addr;
	u8  PS_size;//ͨѶ���ݰ���С
	u8  PS_N;//�����ʻ���N
}SysPara;

//void PS_StaGPIO_Init(void);//��ʼ��PA6��״̬����
	
u8 PS_GetImage(void); //¼��ͼ�� 
 
u8 PS_GenChar(u8 BufferID);//�������� 

u8 PS_Match(void);//��ȷ�ȶ���öָ������ 

u8 PS_Search(u8 BufferID,u16 StartPage,u16 PageNum,SearchResult *p);//����ָ�� 
 
u8 PS_RegModel(void);//�ϲ�����������ģ�壩 
 
u8 PS_StoreChar(u8 BufferID,u16 PageID);//����ģ�� 

u8 PS_DeletChar(u16 PageID,u16 N);//ɾ��ģ�� 

u8 PS_Empty(void);//���ָ�ƿ� 

u8 PS_WriteReg(u8 RegNum,u8 DATA);//дϵͳ�Ĵ��� 
 
u8 PS_ReadSysPara(SysPara *p); //��ϵͳ�������� 

u8 PS_SetAddr(u32 addr);  //����ģ���ַ 

u8 PS_WriteNotepad(u8 NotePageNum,u8 *content);//д���±� 

u8 PS_ReadNotepad(u8 NotePageNum,u8 *note);//������ 

u8 PS_HighSpeedSearch(u8 BufferID,u16 StartPage,u16 PageNum,SearchResult *p);//�������� 
  
u8 PS_ValidTempleteNum(u16 *ValidN);//����Чģ����� 

u8 PS_HandShake(u32 *PS_Addr); //��AS608ģ������

const char *EnsureMessage(u8 ensure);//ȷ���������Ϣ����






extern void delay_ms(u16 nms);
extern uint8_t flag_rx2;

extern uint8_t data_rx2_m[];
extern int len_rx2_m;

// extern uint8_t data_rx2[];
// extern int len_rx2;

extern const char *TAG ;




#define UART_NUM_LCD UART_NUM_1
#define UART_NUM_2G UART_NUM_0//tmp
#define UART_NUM_ZHIWEN UART_NUM_2
#define UART_NUM_LOCK UART_NUM_0
// #define UART_NUM_LOCK SOFTWARE_UART_NUM_3

#define UART_NUM_DUBUG UART_NUM_0

//ESP_LOGI(TAG,"--------JudgeStr err--------!!!\r\n");
// int	_EXFUN(printf, (const char *__restrict, ...)
//                _ATTRIBUTE ((__format__ (__printf__, 1, 2))));

// #define __DEBUG__  
// #ifdef __DEBUG__  
// #define debug_print(format,...) printf("File: "__FILE__", Line: %05d: "format"/n", __LINE__, ##__VA_ARGS__)  
// #else  
// #define DEBUG(format,...)  
// #endif  

#define BAUD_RATE_DB 115200
#define BAUD_RATE_RL 115200
//9600

#define _DEBUG_ 0

#if _DEBUG_
#define DB_PR(...) printf(__VA_ARGS__)
#else
#define DB_PR(...) 
#endif




#define _DEBUG2_ 0
#if _DEBUG2_
#define DB_PR2(...) printf(__VA_ARGS__)
#else
#define DB_PR2(...) 
#endif




#endif
