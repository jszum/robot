
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "robot_map.h"

#define measure_and_set 1
#define	go_forward 2
#define	forward_moving 3
#define turn_normal_R 4
#define	normal_turning 5
#define	turn_avoid_L 6
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

osThreadId emergencyHandle;
osThreadId motor_controlHandle;
osThreadId HCSR04Handle;
osMutexId UART_MutexHandle;
osMutexId distance_mutexHandle;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

//PAPUT
char transmitBuffer[32];
uint8_t uart_in[1];
uint8_t enc_L_EN =0;
uint8_t enc_R_EN =0;
uint8_t enc_L_CNT =0;
uint8_t enc_R_CNT =0;
uint32_t i =0;
uint8_t ticks;
uint8_t is_moving = 0;
uint8_t snake_cnt = 0;
uint8_t snake_to_do = 1;
uint8_t corner_cnt = 0;

void go_Forward (void);
void go_TurnLeft (void);
void go_TurnRight (void);



uint8_t SM_state = measure_and_set;


//ADAM
volatile uint32_t hcsr04_rising_edge;
volatile uint32_t hcsr04_falling_edge;
volatile uint8_t hcsr04_generate_trig = 0;
volatile uint8_t hcsr04_wait_for_rising_edge = 0;
volatile uint8_t hcsr04_wait_for_falling_edge = 0;
uint8_t emergency_brake = 0;

//JAREK
int* map = NULL;
int rows = 20;
int columns = 20;




uint16_t distance =100; //current distance to obstacle [cm], locked by mutex
uint16_t distance_temp;

BaseType_t xHigherPriorityTaskWoken;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
void Startemergency(void const * argument);
void Start_motor_control(void const * argument);
void StartTaskHCSR04(void const * argument);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
//extern void initialise_monitor_handles(void);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1
			&& hcsr04_generate_trig == 1) {
		if (hcsr04_wait_for_falling_edge == 0) {
			__HAL_TIM_SET_COUNTER(htim, 0);
		}
		hcsr04_generate_trig = 0;
		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
		hcsr04_wait_for_rising_edge = 1;
		//printf("INTERRUPT\n");

	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == ECHO_Pin) {
		if (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == 1
				&& hcsr04_wait_for_rising_edge) {
			//printf("1\n");
			hcsr04_rising_edge = __HAL_TIM_GET_COUNTER(&htim2);
			hcsr04_wait_for_rising_edge = 0;
			hcsr04_wait_for_falling_edge = 1;

		}
		if (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == 0
				&& hcsr04_wait_for_falling_edge) {
			//printf("0\n");
			hcsr04_falling_edge = __HAL_TIM_GET_COUNTER(&htim2);
			hcsr04_wait_for_falling_edge = 0;
			xHigherPriorityTaskWoken = pdFALSE;

			xTaskNotifyFromISR(HCSR04Handle, 0, eNoAction,
					&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

			}pdFALSE;
		}
		if (GPIO_Pin == GPIO_PIN_3){
			if (enc_L_EN) {
				enc_L_CNT++;
			}	
			if (enc_L_CNT>=ticks-1) {
						HAL_GPIO_WritePin(MOTOR_L_EN_GPIO_Port, MOTOR_L_EN_Pin, GPIO_PIN_RESET);
						is_moving ++;
						enc_L_EN=0;	
						enc_L_CNT=0;

				}
			if (is_moving==3) is_moving=0;
		} 
		if (GPIO_Pin == GPIO_PIN_5){
			if (enc_R_EN) {
				enc_R_CNT++;
			} 
			if (enc_R_CNT>=ticks-1) {
						HAL_GPIO_WritePin(MOTOR_R_EN_GPIO_Port, MOTOR_R_EN_Pin, GPIO_PIN_RESET);
						is_moving ++;
						enc_R_EN=0;
						enc_R_CNT=0;

				}
				if (is_moving==3) is_moving=0;
		}
//			//printf("%d\n", res);

	

}
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  //PAPUT
  __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);

  //ADAM
  //initialise_monitor_handles();
  	//printf("Hello\n");
  	HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1);
		
	//JAREK
	
	int mapsize = calcAdjustedSize(rows, columns);
//map = (int*)calloc(mapsize, sizeof(int));
	map = allocateMap(rows, columns);
  /* USER CODE END 2 */

  /* Create the mutex(es) */
  /* definition and creation of UART_Mutex */
  osMutexDef(UART_Mutex);
  UART_MutexHandle = osMutexCreate(osMutex(UART_Mutex));

  /* definition and creation of distance_mutex */
  osMutexDef(distance_mutex);
  distance_mutexHandle = osMutexCreate(osMutex(distance_mutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of emergency */
  osThreadDef(emergency, Startemergency, osPriorityRealtime, 0, 128);
  emergencyHandle = osThreadCreate(osThread(emergency), NULL);

  /* definition and creation of motor_control */
  osThreadDef(motor_control, Start_motor_control, osPriorityIdle, 0, 128);
  motor_controlHandle = osThreadCreate(osThread(motor_control), NULL);

  /* definition and creation of HCSR04 */
  osThreadDef(HCSR04, StartTaskHCSR04, osPriorityHigh, 0, 128);
  HCSR04Handle = osThreadCreate(osThread(HCSR04), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
 

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 3, 0);
}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 61;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|MOTOR_R_EN_Pin|MOTOR_L_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MOTOR_L2_Pin|TRIG_Pin|MOTOR_L1_Pin|MOTOR_R2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MOTOR_R1_GPIO_Port, MOTOR_R1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin MOTOR_R_EN_Pin MOTOR_L_EN_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|MOTOR_R_EN_Pin|MOTOR_L_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR_L2_Pin TRIG_Pin MOTOR_L1_Pin MOTOR_R2_Pin */
  GPIO_InitStruct.Pin = MOTOR_L2_Pin|TRIG_Pin|MOTOR_L1_Pin|MOTOR_R2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : ECHO_Pin ENC_L_Pin ENC_R_Pin */
  GPIO_InitStruct.Pin = ECHO_Pin|ENC_L_Pin|ENC_R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MOTOR_R1_Pin */
  GPIO_InitStruct.Pin = MOTOR_R1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MOTOR_R1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */

void go_Forward (void){
		
	ticks=50;
	
		enc_L_CNT=0;
		enc_R_CNT=0;
		
			
		HAL_GPIO_WritePin(MOTOR_R1_GPIO_Port, MOTOR_R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_R2_GPIO_Port, MOTOR_R2_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(MOTOR_L1_GPIO_Port, MOTOR_L1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_L2_GPIO_Port, MOTOR_L2_Pin, GPIO_PIN_RESET);
		enc_L_EN=1;
		enc_R_EN=1;
	if (distance>25){
		is_moving = 1;
		
		HAL_GPIO_WritePin(MOTOR_L_EN_GPIO_Port, MOTOR_L_EN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_R_EN_GPIO_Port, MOTOR_R_EN_Pin, GPIO_PIN_SET);	
	}
			
					
		  
				
}
void go_TurnLeft (void){
	
		ticks=18;
		enc_L_CNT=0;
		enc_R_CNT=0;
		
		
		HAL_GPIO_WritePin(GPIOC, MOTOR_R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, MOTOR_R2_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOB, MOTOR_L1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, MOTOR_L2_Pin, GPIO_PIN_SET);
		
		enc_L_EN=1;
		enc_R_EN=1;
	
		is_moving = 1;
		
		HAL_GPIO_WritePin(MOTOR_L_EN_GPIO_Port, MOTOR_L_EN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_R_EN_GPIO_Port, MOTOR_R_EN_Pin, GPIO_PIN_SET);	

			
}
void go_TurnRight (void){
	
		ticks=18;
		enc_L_CNT=0;
		enc_R_CNT=0;
	
		HAL_GPIO_WritePin(GPIOC, MOTOR_R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, MOTOR_R2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOB, MOTOR_L1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, MOTOR_L2_Pin, GPIO_PIN_RESET);

		enc_L_EN=1;
		enc_R_EN=1;

		is_moving = 1;
	
	  HAL_GPIO_WritePin(MOTOR_L_EN_GPIO_Port, MOTOR_L_EN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_R_EN_GPIO_Port, MOTOR_R_EN_Pin, GPIO_PIN_SET);	
	
}


/* USER CODE END 4 */

/* Startemergency function */
void Startemergency(void const * argument)
{

  /* USER CODE BEGIN 5 */
  /* Infinite loop */

	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 100;


    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
  for(;;)
  {
	  // Wait for the next cycle.
	  vTaskDelayUntil( &xLastWakeTime, xFrequency );
		if (distance>25) {
			if (enc_L_EN) HAL_GPIO_WritePin(MOTOR_L_EN_GPIO_Port, MOTOR_L_EN_Pin, GPIO_PIN_SET);
			if (enc_R_EN) HAL_GPIO_WritePin(MOTOR_R_EN_GPIO_Port, MOTOR_R_EN_Pin, GPIO_PIN_SET);
			emergency_brake = 0;
		}
	  if((distance < 20)&& (!emergency_brake))
	  {
							/*	
			xSemaphoreTake(UART_MutexHandle, portMAX_DELAY);
			//	memset(transmitBuffer,0,strlen(transmitBuffer));
				sprintf((char*)transmitBuffer,"%u cm\r\n",distance);
	  		HAL_UART_Transmit_IT(&huart2,(uint8_t*)transmitBuffer, strlen(transmitBuffer));
					xSemaphoreGive(UART_MutexHandle);*/
		  HAL_GPIO_WritePin(MOTOR_L_EN_GPIO_Port, MOTOR_L_EN_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(MOTOR_R_EN_GPIO_Port, MOTOR_R_EN_Pin, GPIO_PIN_RESET);
		  emergency_brake = 1;
	  }


    //osDelay(10);
  }
  /* USER CODE END 5 */ 
}

/* Start_motor_control function */
void Start_motor_control(void const * argument)
{
  /* USER CODE BEGIN Start_motor_control */
  /* Infinite loop */
  for(;;)
  {
	  	
			switch(SM_state){
			
				case measure_and_set:
				
						if (distance>30) {
							setCellBlockedAtDistance(map, rows, columns, distance/30);
							SM_state = go_forward;
						}	
				break; 
				
				
				case go_forward:
				
							if (isNextCellFree(map, rows, columns)) {
								//go_Forward();
								//SM_state = forward_moving;
						}	
							go_Forward();
							SM_state = forward_moving;
				break; 
				
				
				case forward_moving:
				
						if(!is_moving){
							moveForward(map, rows, columns);
							snake_cnt++;
							if (snake_cnt<snake_to_do){
								SM_state = go_forward;
								break; 
							}	else snake_cnt =0;
							if (corner_cnt) {
								corner_cnt =0;
								snake_to_do++;
							}
							SM_state = turn_normal_R;
							
						}
						
				break; 
							
				
				
				case turn_normal_R:
				
					go_TurnRight();
					SM_state = normal_turning;
				break; 
								
				
				case normal_turning:
				
							if(!is_moving){
								turnRight();
								corner_cnt++;
								SM_state = measure_and_set;
						}
				break; 
						
				
				case turn_avoid_L:
				
				
				break; 
							
			
			
			
			}
				
	xSemaphoreTake(UART_MutexHandle, portMAX_DELAY);
			//	memset(transmitBuffer,0,strlen(transmitBuffer));
				sprintf((char*)transmitBuffer,"%u\r\n",SM_state);
	  		HAL_UART_Transmit_IT(&huart2,(uint8_t*)transmitBuffer, strlen(transmitBuffer));
					xSemaphoreGive(UART_MutexHandle);
	      


				
		
		/*
				i++;
				if (i==150){
				go_Forward();
					
				}else if (i==300){
				go_TurnLeft();
				
				}
				else if (i==450){
				go_TurnRight();
				i=0;
				}
	      osDelay(10);
		*/
  }
  /* USER CODE END Start_motor_control */
}

/* StartTaskHCSR04 function */
void StartTaskHCSR04(void const * argument)
{
  /* USER CODE BEGIN StartTaskHCSR04 */
	//printf("HCSR04 task started\n");
		BaseType_t xResult;

		TickType_t xLastWakeTime;
		const TickType_t xFrequency = 100;

		 //Initialise the xLastWakeTime variable with the current time.
		 xLastWakeTime = xTaskGetTickCount();

		/* Infinite loop */
		for (;;) {
			// Wait for the next cycle.
			 vTaskDelayUntil( &xLastWakeTime, xFrequency );

			if (hcsr04_generate_trig == 0) {
				hcsr04_generate_trig = 1;
				//htim2.Instance -> CNT = 0;
				__HAL_TIM_SET_COUNTER(&htim2, 0);
				HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
				xResult = xTaskNotifyWait(0x00, 0xff, NULL, pdMS_TO_TICKS(50));
				if (xResult == pdPASS) {
					//printf("Notification received\n");

					distance_temp = ((hcsr04_falling_edge - hcsr04_rising_edge)
														* 8 * 0.0208333333) / 58;

					if (distance_mutexHandle != NULL) {
						/* See if we can obtain the semaphore.  If the semaphore is not
						 available wait 10 ticks to see if it becomes free. */
						if ( xSemaphoreTake(distance_mutexHandle,
								(TickType_t ) 10) == pdTRUE) {
							/* We were able to obtain the semaphore and can now access the
							 shared resource. */

							if (distance_temp<650) distance= distance_temp;
							//printf("Distance: %d\n", distance);


							/* We have finished accessing the shared resource.  Release the
							 semaphore. */
							xSemaphoreGive(distance_mutexHandle);
						} else {
							/* We could not obtain the semaphore and can therefore not access
							 the shared resource safely. */
						}
					}

				} else {
					//printf("Notification NOT received\n");

				}
			}


			//osDelay(100);
		}
  /* USER CODE END StartTaskHCSR04 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
