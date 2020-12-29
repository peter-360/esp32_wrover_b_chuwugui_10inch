/* UART Echo Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"


#include "as608.h" 
#include <string.h>
#include <stdlib.h>
//#include "time.h"
#include <sys/time.h>
#include "esp_log.h"

#include "user_app.h"

/**
 * This is an example which echos any data it receives on UART1 back to the sender,
 * with hardware flow control turned off. It does not use UART driver event queue.
 *
 * - Port: UART1
 * - Receive (Rx) buffer: on
 * - Transmit (Tx) buffer: off
 * - Flow control: off
 * - Event queue: off
 * - Pin assignment: see defines below
 */

//#define UART_NUM_LOCK UART_NUM_0
#define ECHO_TEST0_TXD  (GPIO_NUM_1)//2-deng    23     hard UART2 0
#define ECHO_TEST0_RXD  (GPIO_NUM_3)//34        22
#define ECHO_TEST0_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST0_CTS  (UART_PIN_NO_CHANGE)//uart0
    #define RE_485_GPIO     (GPIO_NUM_18)



#define ECHO_TEST_TXD  GPIO_NUM_33//32(GPIO_NUM_33)//GPIO_NUM_4
#define ECHO_TEST_RXD  GPIO_NUM_32//33(GPIO_NUM_32)//GPIO_NUM_5
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)


//xin 1
#define ECHO_TEST2_TXD  (GPIO_NUM_23)//2-deng    23     hard UART2 0
#define ECHO_TEST2_RXD  (GPIO_NUM_34)//34        22
#define ECHO_TEST2_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST2_CTS  (UART_PIN_NO_CHANGE)//zhiwen





#define LED_BLUE     (GPIO_NUM_2)
#define LED_GRREN     (GPIO_NUM_22)
#define LED_RED         (GPIO_NUM_27)



// #define GPIO_OUPUT_IO_2G_RST     GPIO_NUM_19//35//5
#define GPIO_OUPUT_IO_PA_CTL     GPIO_NUM_4


#define GPIO_INPUT_IO_ADMIN     39//4

#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_IO_ADMIN)  )


#define TX1_LEN 12//10//12//10 tupian

#define TX1_LEN_BL 10//8 bianliang










const char *TAG = "MP3_DECODER";



void delay_ms(u16 nms)
{	 	
    vTaskDelay(nms / portTICK_PERIOD_MS);
}
/*??????·?????*/
//????????????,±??????????±????485???í?ê????
#define RS485_RX_EN()			delay_ms(70); gpio_set_level(RE_485_GPIO, 0);delay_ms(70);//rx;  RS485_delay(1000);
//????·???????,±??????????±????485???í?ê????
#define RS485_TX_EN()			delay_ms(70); gpio_set_level(RE_485_GPIO, 1);delay_ms(70);//rx;  RS485_delay(1000);

#define BUF_SIZE (512)

uint8_t data_rx[BUF_SIZE] = {0};
uint16_t len_rx;

uint8_t data_rx0[BUF_SIZE] = {0};//485 dtu debug        data_rx2
int len_rx0;
uint8_t flag_rx0;

uint8_t data_rx2_m[BUF_SIZE] = {0};
int len_rx2_m;
uint8_t flag_rx2;








TaskHandle_t taskhandle_system= NULL;






// static void echo_task2()//lcd
// {
//     //vTaskDelay(1);
    
//     vTaskDelete(NULL);
// }

static void echo_task()
{
    
    // Configure a temporary buffer for the incoming data
    //uint8_t *data_rx = (uint8_t *) malloc(BUF_SIZE);

    //DB_PR("UART1 start recieve loop.\r\n");

    while (1) {
        //vTaskDelay(10 / portTICK_PERIOD_MS);
        // Read data from the UART
        len_rx0 = uart_read_bytes(UART_NUM_0, data_rx0, BUF_SIZE, 20 / portTICK_RATE_MS);
        len_rx = uart_read_bytes(UART_NUM_1, data_rx, BUF_SIZE, 20 / portTICK_RATE_MS);
        len_rx2_m = uart_read_bytes(UART_NUM_2, data_rx2_m, BUF_SIZE, 20 / portTICK_RATE_MS);
        // Write data back to the UART
        
        //uart_write_bytes(UART_NUM_1, (const char *) data_rx, len_rx);//len =0 budayin
        //uart_write_bytes(UART_NUM_2, (const char *) data_rx, len_rx);


        if ((len_rx2_m > 0) ) {
            
            // len_rx2_m = len_rx2_m;
            // memcpy(data_rx2_m,data_rx2_m,len_rx2_m);
            // DB_PR("2rcv_zhiwen_uart2-Received %u bytes:", len_rx2_m);//zhiwen
            // for (int i = 0; i < len_rx2_m; i++) {
            //     DB_PR("0x%.2X ", (uint8_t)data_rx2_m[i]);
            // }
            // DB_PR("] \n");
            
            // flag_rx2 =1;
            // DB_PR("-----2----flag_rx2=%u\r\n", flag_rx2);
            
            // if(taskhandle_uart2!=NULL)
            // {
            //     DB_PR("--uart2--111111-----.\r\n");
            //     vTaskDelete(taskhandle_uart2);
            //     taskhandle_uart2 =NULL;
            // }
            // else
            // {
            //     DB_PR("--uart2--222222 =NULL-----.\r\n");
            // }
            
            // xTaskCreate((TaskFunction_t)echo_task3, "uart_echo_task3",2* 1024, NULL, 2, &taskhandle_uart2);//uart2
			
			uart_write_bytes(UART_NUM_0, (const char *) data_rx2_m, len_rx2_m);
            uart_write_bytes(UART_NUM_2, (const char *) data_rx2_m, len_rx2_m);//--------
        

            // flag_rx0 =1;
            // DB_PR("-----2----flag_rx0=%u\r\n", flag_rx0);
            if(NULL!=strstr((char*)data_rx2_m,"CONNECT OK\r"))
            {
                // iot_2G_connected_flag=1;
                DB_PR3("---------1----------\n");
            }
            else if(NULL!=strstr((char*)data_rx2_m,"CLOSED\r"))
            {
                // iot_2G_connected_flag=0;
                DB_PR3("---------2----------\n");
            }
            else if(NULL!=strstr((char*)data_rx2_m,"AT Ready\r"))
            {
                // iot_2G_connected_flag=0;
                DB_PR3("---------3----------\n");
            }
            else if(NULL!=strstr((char*)data_rx2_m,"OK\r\r"))
            {
                DB_PR3("---------4----------\n");
            }
            else if(NULL!=strstr((char*)data_rx2_m,"+CME ERROR:"))//53   no sim 58
            {
                // iot_2G_connected_flag=0;
                DB_PR3("---------100----------\n");
                // uart_write_bytes(UART_NUM_DUBUG, (const char *) data_rx2_m, len_rx2_m);
                // DB_PR3("ATO\n");
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }
            else //SIM not inserted
            {
                // uart_write_bytes(UART_NUM_DUBUG, (const char *) data_rx2_m, len_rx2_m);//有效数据
                DB_PR3("---------0----------\n");
            }

		
		}

								
		


        if (len_rx > 0) {

            DB_PR("1rcv_lcd_uart1-Received %u bytes:", len_rx);//lcd
            for (int i = 0; i < len_rx; i++) {
                DB_PR("0x%.2X ", (uint8_t)data_rx[i]);
                // if(spear_uart_process_data(data_rx[i]))
                // {
                //     ////send event to 
                //     //spear_sched_set_evt(NULL, 0,user_cmd_process_event_handle);

                //     DB_PR("处理数据2-start\r\n");
                //     xTaskCreate((TaskFunction_t)echo_task2, "uart_echo_task2",4* 1024, NULL, 2, NULL);
                // }
            }
            DB_PR("] \n");

            //vTaskDelay(2 / portTICK_PERIOD_MS);


            // xTaskCreate((TaskFunction_t)echo_task2, "uart_echo_task2",6* 1024, NULL, 2, NULL);//uart1

        }
	

        if (len_rx0 > 0) {

            DB_PR("0rcv_lock_uart0-Received %u bytes:", len_rx0);//485  DTU
            for (int i = 0; i < len_rx0; i++) {
                DB_PR("0x%.2X ", (uint8_t)data_rx0[i]);
            }
            DB_PR("] \n");


            //vTaskDelay(2 / portTICK_PERIOD_MS);
            // xTaskCreate((TaskFunction_t)echo_task0, "uart_echo_task0",2* 1024, NULL, 2, NULL);//uart1
            // uart_write_bytes(UART_NUM_DUBUG, (const char *) data_rx0, len_rx0);//debug todo---------

            RS485_TX_EN();
            uart_write_bytes(UART_NUM_DUBUG, (const char *) data_rx0, len_rx0);//debug todo---------
            RS485_RX_EN();//


        }



    }
    //vTaskDelay(1);
    
    vTaskDelete(NULL);
}


void uart_init_all(void)
{

    // while(1)
    // {
    //     vTaskDelay(50 / portTICK_PERIOD_MS);

    // }
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 115200,// lcd
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
        uart_config_t uart_config0 = {
            .baud_rate = 9600,// lock
            .data_bits = UART_DATA_8_BITS,
            .parity    = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
        };

    uart_config_t uart_config2 = {
        .baud_rate = 115200,//57600,// 4G
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };



#if _DEBUG_
    uart_config0.baud_rate = BAUD_RATE_DB;
#else
    uart_config0.baud_rate = BAUD_RATE_RL; 
#endif


        // Set UART log level
    //Set UART log level
    // esp_log_level_set(TAG, ESP_LOG_INFO);
    //Set UART pins (using UART0 default pins ie no changes.)


    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    // DB_PR("Start ttl application test and configure UART2.\r\n");

    //1 lcd
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);




    //2 指纹
    uart_param_config(UART_NUM_2, &uart_config2);
    uart_set_pin(UART_NUM_2,  ECHO_TEST2_TXD, ECHO_TEST2_RXD, ECHO_TEST2_RTS, ECHO_TEST2_CTS);
    uart_driver_install(UART_NUM_2, BUF_SIZE * 2, 0, 0, NULL, 0);

    // //3 io moni
    // uart_param_config(UART_NUM_3, &uart_config3);
    // uart_set_pin(UART_NUM_3, ECHO_TEST3_TXD, ECHO_TEST3_RXD, ECHO_TEST3_RTS, ECHO_TEST3_CTS);
    // uart_driver_install(UART_NUM_3, BUF_SIZE * 2, 0, 0, NULL, 0);





    // vTaskDelay(1000 / portTICK_PERIOD_MS);//
    //0 2G
    uart_param_config(UART_NUM_0, &uart_config0);

#if 1
        uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
#else
        //uart_set_pin(UART_NUM_0, ECHO_TEST3_TXD, ECHO_TEST3_RXD, ECHO_TEST3_RTS, ECHO_TEST3_CTS);
#endif
    //Install UART driver, and get the queue.
    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);

}



static void gpio_task_system(void* arg)
{
    // uint32_t io_num;
    uint32_t tick_times=0;
    bool led_green_state=0;
    // bool led_blue_state=0;
    for(;;) 
    {
        
        // DB_PR("------------system heart-----------\r\n");
        tick_times++;
        vTaskDelay(10 / portTICK_PERIOD_MS);//on 
		if(tick_times%100==0)
		{

            // if(0==sys_running_flag)
            {
                if(led_green_state == 0)
                {
                    // DB_PR("------------gr led on-----------\r\n");
                    led_green_state =1;
                    //---------system state----------
                    // vTaskDelay(1000 / portTICK_PERIOD_MS);//on 
                    // gpio_set_level(LED_BLUE, 0);
                    gpio_set_level(LED_GRREN, 0);
                    // gpio_set_level(LED_RED, 0);
                }
                else if(led_green_state == 1)
                {
                    // DB_PR("------------gr led off-----------\r\n");
                    led_green_state =0;
                    // vTaskDelay(1000 / portTICK_PERIOD_MS);//off del
                    // gpio_set_level(LED_BLUE, 1);
                    gpio_set_level(LED_GRREN, 1);
                    // gpio_set_level(LED_RED, 1);
                }
                // DB_PR("\r\n");

            }
            // else
            {
                DB_PR("------------system heart-----------\r\n");
                // DB_PR("----GPIO_INPUT_IO_ZW_JC=%d----\r\n",gpio_get_level(GPIO_INPUT_IO_ZW_JC));
            }
            
            
		}
        if(tick_times%500==0)
        {
            time_t rawtime;
            struct tm* timeinfo;
            // char timE[80];

            time(&rawtime);
            int64_t timer_tm = esp_timer_get_time();
            DB_PR("rawtime=%ld,timer_tm=%lld\n",rawtime,timer_tm);
            // DB_PR("rawtime=%ld\n",rawtime);
            rawtime = rawtime + 1603435347;//offset 20201023
            timeinfo=localtime(&rawtime);
            // strftime(timE,80,"Date:\n%Y-%m-%d\nTime:\n%I:%M:%S\n",timeinfo);
            // DB_PR2("%s",timE);

            DB_PR("Local time is: %s\n",asctime(timeinfo));

            // DB_PR("tcp_connected_flag=%d\n",tcp_connected_flag);
        }

    }
    vTaskDelete(NULL);
}











void gpio_int()
{

    DB_PR("-----gpio init----- ... \r\n");

    // gpio_pad_select_gpio(RE_485_GPIO);
    // /* Set the GPIO as a push/pull output */
    // gpio_set_direction(RE_485_GPIO, GPIO_MODE_OUTPUT);
    // RS485_RX_EN();//RS485_TX_EN();


    // //todo 2G DTU



        // gpio_pad_select_gpio(GPIO_OUPUT_IO_2G_RST);
        // /* Set the GPIO as a push/pull output */
        // gpio_set_direction(GPIO_OUPUT_IO_2G_RST, GPIO_MODE_OUTPUT);

        // gpio_set_level(GPIO_OUPUT_IO_2G_RST, 0);
        // vTaskDelay(500 / portTICK_PERIOD_MS);
        // gpio_set_level(GPIO_OUPUT_IO_2G_RST, 1);





    gpio_pad_select_gpio(LED_BLUE);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_BLUE, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_BLUE, 1);


    gpio_pad_select_gpio(LED_GRREN);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_GRREN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_GRREN, 1);


    gpio_pad_select_gpio(LED_RED);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_RED, 1);

    xTaskCreate((TaskFunction_t)gpio_task_system, "gpio_task_system", 2048, NULL, 10, &taskhandle_system);
    // xTaskCreate((TaskFunction_t)gpio_task_example_wifi, "gpio_task_example_wifi", 2048, NULL, 10, &taskhandle_temp_wifi);


    DB_PR("-----gpio init2----- ... \r\n");


    // gpio_pad_select_gpio(emac->int_gpio_num);
    // gpio_set_direction(emac->int_gpio_num, GPIO_MODE_INPUT);
    // gpio_set_pull_mode(emac->int_gpio_num, GPIO_PULLDOWN_ONLY);
    // gpio_set_intr_type(emac->int_gpio_num, GPIO_INTR_POSEDGE);

    // gpio_pad_select_gpio(GPIO_INPUT_IO_ZW_2);
    // /* Set the GPIO as a push/pull output */
    // gpio_set_direction(GPIO_INPUT_IO_ZW_2, GPIO_MODE_INPUT);
    // //gpio_pullup_en(GPIO_INPUT_IO_ZW_2);
    // //gpio_pullup_dis(GPIO_INPUT_IO_ZW_2);
    // gpio_set_pull_mode(GPIO_INPUT_IO_ZW_2,GPIO_PULLUP_ONLY);//GPIO_PULLUP_ONLY


    // gpio_config_t io_conf;
    // io_conf.intr_type    = GPIO_PIN_INTR_DISABLE;
    // io_conf.mode         = GPIO_MODE_INPUT;
    // io_conf.pin_bit_mask = GPIO_INPUT_ZWJC_PIN_SEL;//(1ULL << GPIO_INPUT_IO_ZW_JC);
    // io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;//GPIO_PULLDOWN_DISABLE todo--------
    // io_conf.pull_up_en   = GPIO_PULLUP_DISABLE;
    // gpio_config(&io_conf);


    // xTaskCreate((TaskFunction_t)key_trigger, "key_trigger", 1024 * 2, NULL, 10,NULL);

    user_app_key_init();


}

void uart0_debug_data_h(uint8_t* data,uint16_t len)//hex8
{
    DB_PR("---2----debug_data:");
    for(int i=0;i<len;i++)
        DB_PR("%02x ",data[i]);
    DB_PR("\r\n");
}





static const uint8_t auchCRCHi[] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40
};
 
static const uint8_t auchCRCLo[] = {
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
0x40
};
 
uint16_t CRC16(uint8_t *puchMsg, uint16_t usDataLen)
{
  uint8_t uchCRCHi = 0xFF; // 高CRC字节初始化
  uint8_t uchCRCLo = 0xFF; // 低CRC 字节初始化
  uint32_t uIndex; // CRC循环中的索引
  while (usDataLen--) // 传输消息缓冲区
  {
    uIndex = uchCRCHi ^ *puchMsg++; // 计算CRC
    uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
    uchCRCLo = auchCRCLo[uIndex];
  }
  return (((uint16_t)uchCRCLo << 8u) | uchCRCHi);
}



#if 1
void send_cmd_to_lcd_pic(uint16_t temp)//图片
{
    uint8_t tx_Buffer[50]={0};  
    uint16_t crc16_temp=0;

    DB_PR("-----pic-----.\r\n");
    tx_Buffer[0] = 0x5A;
    tx_Buffer[1] = 0xA5;

    tx_Buffer[2] = 0x09;//len
    tx_Buffer[3] = 0x82;

    tx_Buffer[4] = 0x00;
    tx_Buffer[5] = 0x84;

    tx_Buffer[6] = 0x5A;
    tx_Buffer[7] = 0x01;

        
    tx_Buffer[8] = temp/256;
    tx_Buffer[9] = temp%256;
    DB_PR("temp-pic:0x%04x\r\n",temp);

    //crc
    crc16_temp = CRC16(tx_Buffer+3, TX1_LEN - 5);
    DB_PR("tx CRC16 result:0x%04X\r\n",crc16_temp);

    tx_Buffer[10] = crc16_temp&0xff;
    tx_Buffer[11] = (crc16_temp>>8)&0xff;
    
    uart_write_bytes(UART_NUM_LCD, (const char *) tx_Buffer, TX1_LEN);

    uart0_debug_data_h(tx_Buffer, TX1_LEN);
}

#else

void send_cmd_to_lcd_pic(uint16_t temp)//图片
{
    uint8_t tx_Buffer[50]={0};  
    uint16_t crc16_temp=0;

    DB_PR("-----pic-----.\r\n");
    tx_Buffer[0] = 0x5A;
    tx_Buffer[1] = 0xA5;

    tx_Buffer[2] = 0x07;//len
    tx_Buffer[3] = 0x82;

    tx_Buffer[4] = 0x00;
    tx_Buffer[5] = 0x84;

    tx_Buffer[6] = 0x5A;
    tx_Buffer[7] = 0x01;

        
    tx_Buffer[8] = temp/256;
    tx_Buffer[9] = temp%256;
    DB_PR("temp-pic:0x%04x\r\n",temp);

    // //crc
    // crc16_temp = CRC16(tx_Buffer+3, TX4_PIC_LEN - 5);
    // DB_PR("tx CRC16 result:0x%04X\r\n",crc16_temp);

    // tx_Buffer[10] = crc16_temp&0xff;
    // tx_Buffer[11] = (crc16_temp>>8)&0xff;
    
    uart_write_bytes(UART_NUM_LCD, (const char *) tx_Buffer, TX1_LEN);
	// Usart_SendArray( UART4,tx_Buffer,TX4_PIC_LEN);

    uart0_debug_data_h(tx_Buffer, TX1_LEN);
}
#endif

void app_main()
{
    // xTaskCreate(echo_task, "uart_echo_task", 1024, NULL, 10, NULL);
    esp_log_level_set(TAG, ESP_LOG_NONE);//ESP_LOG_INFO

    gpio_pad_select_gpio(RE_485_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(RE_485_GPIO, GPIO_MODE_OUTPUT);
    //RCV MODE
    RS485_RX_EN();//RS485_TX_EN();
    
    uart_init_all();


    vTaskDelay(200 / portTICK_PERIOD_MS);
    send_cmd_to_lcd_pic(0x0000);

    xTaskCreate(echo_task, "uart_echo_task", 2*1024, NULL, 10, NULL);

    vTaskDelay(1200 / portTICK_PERIOD_MS);
    gpio_int();




    send_cmd_to_lcd_pic(0x0026);
    // send_cmd_to_lcd_pic(0x0001);
}
