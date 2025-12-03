/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


#include "usart.h"
#include <string.h>

#include "oled.h"
#include "fonts.h"
#include "tasks.h"

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

//  osThreadDef(Task_GameTick, StartTaskGameTick, osPriorityNormal, 0, 128);
//  Task_GameTickHandle = osThreadCreate(osThread(Task_GameTick), NULL);

  vQueueAddToRegistry(myQueue01Handle, "queue1");

}


