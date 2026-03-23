
/********************** inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "cmsis_os.h"
#include "board.h"
#include "logger.h"
#include "dwt.h"

#include <ao_led.h>

/********************** macros and definitions *******************************/

#define QUEUE_LENGTH_            (1)
#define QUEUE_ITEM_SIZE_         (sizeof(ao_led_message_t))

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/

/********************** internal functions definition ************************/

static void task_(void *argument)
{
  ao_led_handle_t* hao = (ao_led_handle_t*)argument;

  while (true)
  {
    ao_led_message_t msg;

    if (pdPASS == xQueueReceive(hao->hqueue, &msg, portMAX_DELAY))
    {
      switch (msg.action) {
        case AO_LED_MESSAGE_ON:
          LOGGER_INFO("led %d ON", hao->color);
          HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,SET);
          break;

        case AO_LED_MESSAGE_OFF:
          LOGGER_INFO("led %d OFF", hao->color);
          HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,RESET);
          break;

        case AO_LED_MESSAGE_FLASH:
          LOGGER_INFO("led %d FLASH", hao->color);
          HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,SET);
          vTaskDelay(pdMS_TO_TICKS(100));
          HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,RESET);
          break;

        default:
          break;
      }
    }
  }
}

/********************** external functions definition ************************/

bool ao_led_send(ao_led_handle_t* hao, ao_led_message_t pmsg)
{
  return (pdPASS == xQueueSend(hao->hqueue, (void*)&pmsg, 0));
}

void ao_led_init(ao_led_handle_t* hao, ao_led_color color)
{
  hao->color = color;
  hao->hqueue = xQueueCreate(QUEUE_LENGTH_, QUEUE_ITEM_SIZE_);

  while (NULL == hao->hqueue)
  {
    // error
  }

  BaseType_t status;
  status = xTaskCreate(task_, "task_ao", 128, hao, tskIDLE_PRIORITY, &hao->htask);
  while (pdPASS != status)
  {
    // error
  }
}

/********************** end of file ******************************************/
