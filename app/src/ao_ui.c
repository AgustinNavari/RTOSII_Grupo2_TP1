
/********************** inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "cmsis_os.h"
#include "board.h"
#include "logger.h"
#include "dwt.h"

#include "ao_ui.h"
#include "ao_led.h"

/********************** macros and definitions *******************************/

#define QUEUE_LENGTH_            (1)
#define QUEUE_ITEM_SIZE_         (sizeof(msg_event_t))

/********************** internal data declaration ****************************/

typedef struct
{
    QueueHandle_t hqueue;
} ao_ui_handle_t;

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

static ao_ui_handle_t hao_ui;

/********************** external data definition *****************************/

extern ao_led_handle_t led_red;
extern ao_led_handle_t led_green;
extern ao_led_handle_t led_blue;

/********************** internal functions definition ************************/

static void task_(void *argument)
{
  //int id = 0;
  ao_led_message_t led_msg;
  led_msg.action = AO_LED_MESSAGE_OFF;
  ao_led_send(&led_red, led_msg);
  ao_led_send(&led_green, led_msg);
  ao_led_send(&led_blue, led_msg);


  while (true)
  {
    //ao_led_message_t led_msg;
    //led_msg.callback = callback_;
    //led_msg.id = ++id;
    //led_msg.action = AO_LED_MESSAGE_BLINK;
    //led_msg.value = 5000;

    msg_event_t event_msg;


    if (pdPASS == xQueueReceive(hao_ui.hqueue, &event_msg, portMAX_DELAY))
    {
      led_msg.action = AO_LED_MESSAGE_FLASH;
      switch (event_msg)
      {
        case MSG_EVENT_BUTTON_PULSE:
          LOGGER_INFO("led red_ui");
          ao_led_send(&led_red, led_msg);
          break;
        case MSG_EVENT_BUTTON_SHORT:
          LOGGER_INFO("led green_ui");
          ao_led_send(&led_green, led_msg);
          break;
        case MSG_EVENT_BUTTON_LONG:
          LOGGER_INFO("led blue_ui");
          ao_led_send(&led_blue, led_msg);
          break;
        default:
          break;
      }
    }
  }
}

/********************** external functions PULSEdefinition ************************/

bool ao_ui_send_event(msg_event_t msg)
{
  return (pdPASS == xQueueSend(hao_ui.hqueue, (void*)&msg, 0));
}


void ao_ui_init(void)
{
  hao_ui.hqueue = xQueueCreate(QUEUE_LENGTH_, QUEUE_ITEM_SIZE_);
  while(NULL == hao_ui.hqueue)
  {
    // error
  }

  BaseType_t status;
  status = xTaskCreate(task_, "task_ao_ui", 128, NULL, tskIDLE_PRIORITY, NULL);
  while (pdPASS != status)
  {
    // error
  }
}

/********************** end of file ******************************************/

