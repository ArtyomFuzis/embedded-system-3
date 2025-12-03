

#ifndef INC_TASKS_H_
#define INC_TASKS_H_

extern  osMessageQId myQueue01Handle;

extern osThreadId Task_OLEDHandle;
extern osThreadId Task_LED1Handle;
extern osThreadId Task_LED2Handle;
extern osThreadId Task_GameTickHandle;
extern osThreadId Task_MoveFigure;

void StartTaskLED1(void const * argument);
void StartTasLED2(void const * argument);
void StartTaskOLED(void const * argument);
void StartTaskGameTick(void const * argument);
void StartTaskMoveFigure(void const * argument);


#endif
