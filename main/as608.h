#ifndef __AS608_H
#define __AS608_H
#include <stdio.h>
//#include "stm32f4xx.h"  

typedef uint64_t  u64;
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
















extern void log_release(void);
extern void send_cmd_to_lcd_pic(uint16_t temp);
extern void re_smartconfig_wifi(void);

extern void delay_ms(u16 nms);
extern uint8_t flag_rx2;

extern uint8_t data_rx2_m[];
extern int len_rx2_m;

// extern uint8_t data_rx2[];
// extern int len_rx2;

// extern const char *TAG ;




#define UART_NUM_LCD UART_NUM_1
#define UART_NUM_2G UART_NUM_0//tmp
#define UART_NUM_ZHIWEN UART_NUM_2
#define UART_NUM_LOCK UART_NUM_0
// #define UART_NUM_LOCK SOFTWARE_UART_NUM_3     uartlock_output

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
#define BAUD_RATE_RL 9600
//9600


//for main debug, 0 or 1
#define _DEBUG_ 1
#if _DEBUG_
#define DB_PR(...) printf(__VA_ARGS__)
#else
#define DB_PR(...) 
#endif


//for key press 10ci debug,    1
#define _DEBUG2_ 1
#if _DEBUG2_
#define DB_PR2(...) printf(__VA_ARGS__)
#else
#define DB_PR2(...) 
#endif


//for 2G debug,   1
#define _DEBUG3_ 1
#if _DEBUG3_
#define DB_PR3(...) printf(__VA_ARGS__)
#else
#define DB_PR3(...) 
#endif



#endif

