#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "shared.h"

#include "usart.h"
#include <string.h>
#include "tetr.h"

#include "oled.h"
#include "fonts.h"

#include "tasks.h"


osThreadId Task_OLEDHandle;
osThreadId Task_LED1Handle;
osThreadId Task_LED2Handle;
osThreadId Task_GameTickHandle;

osMessageQId myQueue01Handle;

void update_time() {
	for(int i = 0 ; i < FIELD_WIDTH; i++){
		for(int j = 0 ; j < FIELD_HEIGHT; j++){
			if(field[i][j]) oled_DrawBlock(i*BLOCK_SIZE,j*BLOCK_SIZE);
			else oled_ClearBlock(i*BLOCK_SIZE,j*BLOCK_SIZE);
		}
	}

    oled_UpdateScreen();
}

void StartTaskOLED(void const * argument)
{
  for(;;)
  {
    update_time();
    osDelay(10); // Задержка 10 мс (как было в оригинальном коде)
  }
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

void StartTaskGameTick(void const * argument){
	for(;;)
	{
		field[BASE_WIDTH][BASE_HEIGHT] = 0x0;
		field[BASE_WIDTH-1][BASE_HEIGHT] = 0x0;
		field[BASE_WIDTH-2][BASE_HEIGHT] = 0x0;
		field[BASE_WIDTH-3][BASE_HEIGHT] = 0x0;
		field[BASE_WIDTH][BASE_HEIGHT+1] = 0x0;
		field[BASE_WIDTH-1][BASE_HEIGHT+1] = 0x0;
		field[BASE_WIDTH-2][BASE_HEIGHT+1] = 0x0;
		field[BASE_WIDTH-3][BASE_HEIGHT+1] = 0x0;
		field[BASE_WIDTH][BASE_HEIGHT-1] = 0x0;
		field[BASE_WIDTH-1][BASE_HEIGHT-1] = 0x0;
		field[BASE_WIDTH-2][BASE_HEIGHT-1] = 0x0;
		field[BASE_WIDTH-3][BASE_HEIGHT-1] = 0x0;
		generateFigure();
		osDelay(2000);
	}
}
