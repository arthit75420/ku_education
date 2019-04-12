/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define UPDATE_INTERVAL 	15 //refresh rate: 1/0.015ms = 66Hz
#define TASK_INTERVAL			10000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId MAIN_TASKHandle;
osThreadId CircularRingHandle;
osThreadId HeartBeatHandle;
osThreadId AllColorsHandle;
osThreadId ColorWheelHandle;
osThreadId PatternMoveHandle;
osThreadId FullEmptyHandle;
osThreadId AlternateColorsHandle;
osTimerId UpdateTimerHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Main_Task(void const * argument);
void CircularRing_Task(void const * argument);
void HeartBeat_Task(void const * argument);
void AllColors_Task(void const * argument);
void ColorWheel_Task(void const * argument);
void PatternMove_Task(void const * argument);
void FullEmpty_Task(void const * argument);
void AlternateColors_Task(void const * argument);
void vTimerUpdateCallback(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	/* Create task */
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of UpdateTimer */
  osTimerDef(UpdateTimer, vTimerUpdateCallback);
  UpdateTimerHandle = osTimerCreate(osTimer(UpdateTimer), osTimerPeriodic, (void*) 1);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
	osTimerStart(UpdateTimerHandle, UPDATE_INTERVAL);

  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityLow, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of MAIN_TASK */
  osThreadDef(MAIN_TASK, Main_Task, osPriorityHigh, 0, 128);
  MAIN_TASKHandle = osThreadCreate(osThread(MAIN_TASK), NULL);

  /* definition and creation of CircularRing */
  osThreadDef(CircularRing, CircularRing_Task, osPriorityNormal, 0, 128);
  CircularRingHandle = osThreadCreate(osThread(CircularRing), NULL);

  /* definition and creation of HeartBeat */
  osThreadDef(HeartBeat, HeartBeat_Task, osPriorityNormal, 0, 128);
  HeartBeatHandle = osThreadCreate(osThread(HeartBeat), NULL);

  /* definition and creation of AllColors */
  osThreadDef(AllColors, AllColors_Task, osPriorityNormal, 0, 128);
  AllColorsHandle = osThreadCreate(osThread(AllColors), NULL);

  /* definition and creation of ColorWheel */
  osThreadDef(ColorWheel, ColorWheel_Task, osPriorityNormal, 0, 128);
  ColorWheelHandle = osThreadCreate(osThread(ColorWheel), NULL);

  /* definition and creation of PatternMove */
  osThreadDef(PatternMove, PatternMove_Task, osPriorityNormal, 0, 128);
  PatternMoveHandle = osThreadCreate(osThread(PatternMove), NULL);

  /* definition and creation of FullEmpty */
  osThreadDef(FullEmpty, FullEmpty_Task, osPriorityNormal, 0, 128);
  FullEmptyHandle = osThreadCreate(osThread(FullEmpty), NULL);

  /* definition and creation of AlternateColors */
  osThreadDef(AlternateColors, AlternateColors_Task, osPriorityNormal, 0, 128);
  AlternateColorsHandle = osThreadCreate(osThread(AlternateColors), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Main_Task */
/**
* @brief Function implementing the MAIN_TASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Main_Task */
void Main_Task(void const * argument)
{
  /* USER CODE BEGIN Main_Task */
	osThreadSuspend(CircularRingHandle);
	osThreadSuspend(HeartBeatHandle);
	osThreadSuspend(AllColorsHandle);
	osThreadSuspend(ColorWheelHandle);
	osThreadSuspend(PatternMoveHandle);
	osThreadSuspend(FullEmptyHandle);
	osThreadSuspend(AlternateColorsHandle);

	while (1) {
		osThreadResume(CircularRingHandle);
		osDelay(TASK_INTERVAL);
		osThreadSuspend(CircularRingHandle);
		
		osThreadResume(HeartBeatHandle);
		osDelay(TASK_INTERVAL);
		osThreadSuspend(HeartBeatHandle);
		
		osThreadResume(AllColorsHandle);
		osDelay(TASK_INTERVAL);
		osThreadSuspend(AllColorsHandle);

		osThreadResume(ColorWheelHandle);
		osDelay(TASK_INTERVAL);
		osThreadSuspend(ColorWheelHandle);

		osThreadResume(PatternMoveHandle);
		osDelay(TASK_INTERVAL);
		osThreadSuspend(PatternMoveHandle);

		osThreadResume(FullEmptyHandle);
		osDelay(TASK_INTERVAL);
		osThreadSuspend(FullEmptyHandle);
		
		osThreadResume(AlternateColorsHandle);
		osDelay(TASK_INTERVAL);
		osThreadSuspend(AlternateColorsHandle);

	}
  /* USER CODE END Main_Task */
}

/* USER CODE BEGIN Header_CircularRing_Task */
/**
* @brief Function implementing the CircularRing thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CircularRing_Task */
void CircularRing_Task(void const * argument)
{
  /* USER CODE BEGIN CircularRing_Task */
	stripEffect_CircularRing(50, 0, 0, 20);
  /* USER CODE END CircularRing_Task */
}

/* USER CODE BEGIN Header_HeartBeat_Task */
/**
* @brief Function implementing the HeartBeat thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_HeartBeat_Task */
void HeartBeat_Task(void const * argument)
{
  /* USER CODE BEGIN HeartBeat_Task */
	stripEffect_HeartBeat(700, 64, 0, 16);
  /* USER CODE END HeartBeat_Task */
}

/* USER CODE BEGIN Header_AllColors_Task */
/**
* @brief Function implementing the AllColors thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AllColors_Task */
void AllColors_Task(void const * argument)
{
  /* USER CODE BEGIN AllColors_Task */
	stripEffect_AllColors(10);
  /* USER CODE END AllColors_Task */
}

/* USER CODE BEGIN Header_ColorWheel_Task */
/**
* @brief Function implementing the ColorWheel thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ColorWheel_Task */
void ColorWheel_Task(void const * argument)
{
  /* USER CODE BEGIN ColorWheel_Task */
	stripEffect_ColorWheel(50);
  /* USER CODE END ColorWheel_Task */
}

/* USER CODE BEGIN Header_PatternMove_Task */
/**
* @brief Function implementing the PatternMove thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PatternMove_Task */
void PatternMove_Task(void const * argument)
{
  /* USER CODE BEGIN PatternMove_Task */
	stripEffect_PatternMove(50, 2, 10, 10, 10);
  /* USER CODE END PatternMove_Task */
}

/* USER CODE BEGIN Header_FullEmpty_Task */
/**
* @brief Function implementing the FullEmpty thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FullEmpty_Task */
void FullEmpty_Task(void const * argument)
{
  /* USER CODE BEGIN FullEmpty_Task */
  stripEffect_FullEmpty(50, 20, 20, 20);
  /* USER CODE END FullEmpty_Task */
}

/* USER CODE BEGIN Header_AlternateColors_Task */
/**
* @brief Function implementing the AlternateColors thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AlternateColors_Task */
void AlternateColors_Task(void const * argument)
{
  /* USER CODE BEGIN AlternateColors_Task */
  stripEffect_AlternateColors(1000, 10, 50, 0, 0, 0, 0, 50);
  /* USER CODE END AlternateColors_Task */
}

/* vTimerUpdateCallback function */
void vTimerUpdateCallback(void const * argument)
{
  /* USER CODE BEGIN vTimerUpdateCallback */
  ws2812_update();
  /* USER CODE END vTimerUpdateCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
