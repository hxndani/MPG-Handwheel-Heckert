/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MPG_AXIS_B_Pin GPIO_PIN_4
#define MPG_AXIS_B_GPIO_Port GPIOA
#define MPG_AXIS_Z_Pin GPIO_PIN_5
#define MPG_AXIS_Z_GPIO_Port GPIOA
#define MPG_AXIS_Y_Pin GPIO_PIN_6
#define MPG_AXIS_Y_GPIO_Port GPIOA
#define MPG_AXIS_X_Pin GPIO_PIN_7
#define MPG_AXIS_X_GPIO_Port GPIOA
#define MPG_X1_Pin GPIO_PIN_0
#define MPG_X1_GPIO_Port GPIOB
#define MPG_X10_Pin GPIO_PIN_1
#define MPG_X10_GPIO_Port GPIOB
#define MPG_X100_Pin GPIO_PIN_10
#define MPG_X100_GPIO_Port GPIOB
#define LED_MPG_X1_Pin GPIO_PIN_7
#define LED_MPG_X1_GPIO_Port GPIOB
#define LED_MPG_X10_Pin GPIO_PIN_8
#define LED_MPG_X10_GPIO_Port GPIOB
#define LED_MPG_X100_Pin GPIO_PIN_9
#define LED_MPG_X100_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
