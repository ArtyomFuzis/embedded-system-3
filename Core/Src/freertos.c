/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


#include "usart.h"
#include <string.h>

#include "oled.h"
#include "fonts.h"


osThreadId Task_OLEDHandle;
osThreadId Task_LED1Handle;
osThreadId Task_LED2Handle;
osMessageQId myQueue01Handle;



void StartTaskLED1(void const * argument);
void StartTasLED2(void const * argument);
void StartTaskOLED(void const * argument);

void MX_FREERTOS_Init(void);

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );


void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

__weak void configureTimerForRunTimeStats(void)
{

}

__weak unsigned long getRunTimeCounterValue(void)
{
return 0;
}
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
void MX_FREERTOS_Init(void) {
  osMessageQDef(myQueue01, 16, uint16_t);
  myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);
  osThreadDef(Task_LED1, StartTaskLED1, osPriorityNormal, 0, 128);
  Task_LED1Handle = osThreadCreate(osThread(Task_LED1), NULL);


  osThreadDef(Task_LED2, StartTasLED2, osPriorityNormal, 0, 128);
  Task_LED2Handle = osThreadCreate(osThread(Task_LED2), NULL);

  osThreadDef(Task_OLED, StartTaskOLED, osPriorityNormal, 0, 128);
  Task_OLEDHandle = osThreadCreate(osThread(Task_OLED), NULL);

  vQueueAddToRegistry(myQueue01Handle, "queue1");

}


void StartTaskOLED(void const * argument)
{
  for(;;)
  {
    update_time();
    osDelay(10); // Задержка 10 мс (как было в оригинальном коде)
  }
}

void update_time() {
    oled_SetCursor(20, 10);
    oled_SetCursor(47, 30);
    oled_WriteChar('3', Font_7x10, White);
    oled_WriteChar('3', Font_7x10, White);
    oled_WriteChar(':', Font_7x10, White);
    oled_WriteChar('3', Font_7x10, White);
    oled_WriteChar('3', Font_7x10, White);

    oled_UpdateScreen();
}

void StartTaskLED1(void const * argument)
{
  uint32_t state;
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
	  if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_15) == GPIO_PIN_SET) {
		  state = 0x01;
		  osMessagePut(myQueue01Handle, state, 100);
	  } else {
		  state = 0x00;
		  osMessagePut(myQueue01Handle, state, 100);
	  }
	  osDelay(500);
  }
}

void StartTasLED2(void const * argument)
{
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
	  osDelay(400);
  }
}

