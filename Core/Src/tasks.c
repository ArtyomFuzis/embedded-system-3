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
#include "kb.h"

osThreadId Task_OLEDHandle;
osThreadId Task_LED1Handle;
osThreadId Task_LED2Handle;
osThreadId Task_GameTickHandle;
osThreadId Task_MoveFigure;

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


int fall_state = 0;
struct TetrEntity entity;
void StartTaskGameTick(void const * argument){
	for(;;)
	{
		if(!fall_state) {
			struct TetrGenerateReturn res = generate_figure();
			entity = res.entity;
			fall_state = 1;
		}
		fall_state += move_down_figure(&entity);
		if(fall_state > 3){
			clear_lines();
			fall_state = 0;
		}
		osDelay(500);
	}
}

uint8_t Row[4] = {ROW1, ROW2, ROW3, ROW4};

void StartTaskMoveFigure(void const * argument){
	for(;;)
	{
		if(!fall_state){
			continue;
		}
		uint8_t  cur_key = Check_Row(Row[0]);
		if(cur_key == 0x04){
			move_left_figure(&entity);
		} else if(cur_key == 0x02){
			rotate_figure_left(&entity);
		}
		cur_key = Check_Row(Row[2]);
		if(cur_key == 0x04){
			move_right_figure(&entity);
		} else if(cur_key == 0x02){
			rotate_figure_right(&entity);
		}
		cur_key = Check_Row(Row[1]);
		if(cur_key == 0x04){
			move_down_figure(&entity);
		}

		osDelay(40);
	}
}
