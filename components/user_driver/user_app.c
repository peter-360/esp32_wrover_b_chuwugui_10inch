/** 
* @file         user_app.c
* @brief        用户实现自己功能相关函数定义
* @details      定义用户所需的结构体变量以及局部全局变量定义
* @author       Helon_Chan 
* @par Copyright (c):  
*               红旭无线开发团队
* @par History:          
*               Ver0.0.1:
                     Helon_Chan, 2018/06/19, 初始化版本\n 
*/
/*
===========================
头文件包含
=========================== 
*/
#include "user_key.h"
#include <esp_log.h>


#include "as608.h" 
/* 填充需要配置的按键个数以及对应的相关参数 */
static key_config_t gs_m_key_config[BOARD_BUTTON_COUNT] =
{
  {BOARD_BUTTON,APP_KEY_ACTIVE_LOW,0,LONG_PRESSED_TIMER},
};

/** 
 * 用户的短按处理函数
 * @param[in]   key_num                 :短按按键对应GPIO口
 * @param[in]   short_pressed_counts    :短按按键对应GPIO口按下的次数,这里用不上
 * @retval      null
 * @par         修改日志 
 *               Ver0.0.1:
                     Helon_Chan, 2018/06/16, 初始化版本\n 
 */
void short_pressed_cb(uint8_t key_num,uint8_t *short_pressed_counts)
{ 
  DB_PR("*short_pressed_counts=%d\n",*short_pressed_counts);
  switch (key_num)
  {
    case BOARD_BUTTON:
      switch (*short_pressed_counts)
      {
      case 1:
        DB_PR("first press!!!\n");//todo lcd admin
        DB_PR("------------admin mode-----------\r\n");// no print???
        send_cmd_to_lcd_pic(0x0011);

        break;
      // case 2:
      //   DB_PR("double press!!!\n");
      //   break;
      // case 3:
      //   DB_PR("trible press!!!\n");
      //   break;
      // case 4:
      //   DB_PR("quatary press!!!\n");
      //   break;

      case 10:
        DB_PR("ten press!!!\n");//todo log
        log_release();

        break;

        // case ....:
        // break;
      default:
        DB_PR("other press!!!\n");
      }
      *short_pressed_counts = 0;
      break;
  
    default:
      break;
  }
}

/** 
 * 用户的长按处理函数
 * @param[in]   key_num                 :短按按键对应GPIO口
 * @param[in]   long_pressed_counts     :按键对应GPIO口按下的次数,这里用不上
 * @retval      null
 * @par         修改日志 
 *               Ver0.0.1:
                     Helon_Chan, 2018/06/16, 初始化版本\n 
 */
void long_pressed_cb(uint8_t key_num,uint8_t *long_pressed_counts)
{
  switch (key_num)
  {
    case BOARD_BUTTON:
      DB_PR("long press!!!\n");    //todo wifi smartconfig
      re_smartconfig_wifi();
      break;
    default:
      break;
  }
}
















// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#define BUTTON_IO_NUM  GPIO_NUM_39
//39//0
#define BUTTON_ACTIVE_LEVEL   0
#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

#include "unity.h"
#include "iot_button.h"
#include "esp_system.h"
#include "esp_log.h"

#include "string.h"

static const char* TAG_BTN = "BTN_TEST";

void button_tap_cb(void* arg)
{
    char* pstr = (char*) arg;
    DB_PR( "tap cb (%s), heap: %d\n", pstr, esp_get_free_heap_size());
    if(NULL!=strstr(pstr,"TAP"))
    {
      DB_PR("------1-----short press--------------\n");
      send_cmd_to_lcd_pic(0x0011);
    }
}

void button_press_2s_cb(void* arg)
{
    DB_PR( "------2------press 2s, heap: %d\n", esp_get_free_heap_size());
    // re_smartconfig_wifi();

}

void button_press_5s_cb(void* arg)
{
    DB_PR( "------3------press 20s, heap: %d\n", esp_get_free_heap_size());
    // log_release();
}

void button_test()
{
    DB_PR("before btn init, heap: %d\n", esp_get_free_heap_size());
    button_handle_t btn_handle = iot_button_create(BUTTON_IO_NUM, BUTTON_ACTIVE_LEVEL);
    iot_button_set_evt_cb(btn_handle, BUTTON_CB_PUSH, button_tap_cb, "PUSH");
    iot_button_set_evt_cb(btn_handle, BUTTON_CB_RELEASE, button_tap_cb, "RELEASE");
    iot_button_set_evt_cb(btn_handle, BUTTON_CB_TAP, button_tap_cb, "TAP");
    iot_button_set_serial_cb(btn_handle, 2, 1000/portTICK_RATE_MS, button_tap_cb, "SERIAL");

    iot_button_add_custom_cb(btn_handle, 2, button_press_2s_cb, NULL);
    iot_button_add_custom_cb(btn_handle, 15, button_press_5s_cb, NULL);//5s->15s
    DB_PR("after btn init, heap: %d\n", esp_get_free_heap_size());

    // vTaskDelay(1000 / portTICK_PERIOD_MS);
    // DB_PR("free btn: heap:%d\n", esp_get_free_heap_size());
    // iot_button_delete(btn_handle);
    // DB_PR("after free btn: heap:%d\n", esp_get_free_heap_size());
}





/** 
 * 用户的按键初始化函数
 * @param[in]   null 
 * @retval      null
 * @par         修改日志 
 *               Ver0.0.1:
                     Helon_Chan, 2018/06/16, 初始化版本\n 
 */
void user_app_key_init(void)
{
    // int32_t err_code;
    // err_code = user_key_init(gs_m_key_config,BOARD_BUTTON_COUNT,DECOUNE_TIMER,long_pressed_cb,short_pressed_cb);
    // ESP_LOGI("user_app_key_init","user_key_init is %d\n",err_code);//no use, with wifi conflict

    button_test();
    DB_PR("-----------user_app_key_init--------------\n");

    
}