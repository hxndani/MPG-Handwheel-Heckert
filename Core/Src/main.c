/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include "usbd_cdc_if.h"
#include <string.h>
#include <stdio.h>

uint8_t Read_MPG_Mult(void)
{
    if (!HAL_GPIO_ReadPin(MPG_X1_GPIO_Port, MPG_X1_Pin))   return 0b00000100; // x1
    if (!HAL_GPIO_ReadPin(MPG_X10_GPIO_Port, MPG_X10_Pin)) return 0b00000010; // x10
    if (!HAL_GPIO_ReadPin(MPG_X100_GPIO_Port, MPG_X100_Pin))return 0b00000001; // x100
    return 0;
}

uint8_t Read_MPG_Axis(void)
{
    if (!HAL_GPIO_ReadPin(MPG_AXIS_X_GPIO_Port, MPG_AXIS_X_Pin)) return 0b10000000; //axis x
    if (!HAL_GPIO_ReadPin(MPG_AXIS_Y_GPIO_Port, MPG_AXIS_Y_Pin)) return 0b01000000; // y
    if (!HAL_GPIO_ReadPin(MPG_AXIS_Z_GPIO_Port, MPG_AXIS_Z_Pin)) return 0b00100000; // z
    if (!HAL_GPIO_ReadPin(MPG_AXIS_B_GPIO_Port, MPG_AXIS_B_Pin)) return 0b00001000; // b
    return 0;
}

void Update_MPG_LED(uint8_t mult)
{
    HAL_GPIO_WritePin(GPIOB,
        LED_MPG_X1_Pin|LED_MPG_X10_Pin|LED_MPG_X100_Pin,
        GPIO_PIN_RESET);

    if (mult & 0b00000100)
        HAL_GPIO_WritePin(LED_MPG_X1_GPIO_Port, LED_MPG_X1_Pin, SET);
    else if (mult & 0b00000010)
        HAL_GPIO_WritePin(LED_MPG_X10_GPIO_Port, LED_MPG_X10_Pin, SET);
    else if (mult & 0b00000001)
        HAL_GPIO_WritePin(LED_MPG_X100_GPIO_Port, LED_MPG_X100_Pin, SET);
}

void CDC_Print(char *msg)
{
    CDC_Transmit_FS((uint8_t*)msg, strlen(msg));
}

void Print_Verbose(uint8_t state)
{
    char buf[32];
    char bits[9];

    for(int i = 0; i < 8; i++)
        bits[i] = (state & (1 << (7 - i))) ? '1' : '0';

    bits[8] = '\0';

    sprintf(buf, "X:%s\r\n", bits);
    CDC_Print(buf);
}




/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


	  uint8_t axis = Read_MPG_Axis();
	  uint8_t mult = Read_MPG_Mult();

	  uint8_t state = axis | mult;

	  Update_MPG_LED(mult);

	  Print_Verbose(state);


	  HAL_Delay(1);
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_MPG_X1_Pin|LED_MPG_X10_Pin|LED_MPG_X100_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MPG_AXIS_B_Pin MPG_AXIS_Z_Pin MPG_AXIS_Y_Pin MPG_AXIS_X_Pin */
  GPIO_InitStruct.Pin = MPG_AXIS_B_Pin|MPG_AXIS_Z_Pin|MPG_AXIS_Y_Pin|MPG_AXIS_X_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : MPG_X1_Pin MPG_X10_Pin MPG_X100_Pin */
  GPIO_InitStruct.Pin = MPG_X1_Pin|MPG_X10_Pin|MPG_X100_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_MPG_X1_Pin LED_MPG_X10_Pin LED_MPG_X100_Pin */
  GPIO_InitStruct.Pin = LED_MPG_X1_Pin|LED_MPG_X10_Pin|LED_MPG_X100_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
