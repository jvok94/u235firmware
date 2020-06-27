/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32l0xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SWUP_Pin GPIO_PIN_9
#define SWUP_GPIO_Port GPIOB
#define SWDN_Pin GPIO_PIN_14
#define SWDN_GPIO_Port GPIOC
#define OSCEN_Pin GPIO_PIN_15
#define OSCEN_GPIO_Port GPIOC
#define CLK_Pin GPIO_PIN_0
#define CLK_GPIO_Port GPIOA
#define nRFEN_Pin GPIO_PIN_1
#define nRFEN_GPIO_Port GPIOA
#define TXD_Pin GPIO_PIN_2
#define TXD_GPIO_Port GPIOA
#define nPWRDN_Pin GPIO_PIN_3
#define nPWRDN_GPIO_Port GPIOA
#define DIVIN_Pin GPIO_PIN_4
#define DIVIN_GPIO_Port GPIOA
#define SCLK_Pin GPIO_PIN_5
#define SCLK_GPIO_Port GPIOA
#define nDISP_CS_Pin GPIO_PIN_6
#define nDISP_CS_GPIO_Port GPIOA
#define DIVOUT_Pin GPIO_PIN_7
#define DIVOUT_GPIO_Port GPIOA
#define MOSI_Pin GPIO_PIN_1
#define MOSI_GPIO_Port GPIOB
#define REFOUT_Pin GPIO_PIN_9
#define REFOUT_GPIO_Port GPIOA
#define RXD_Pin GPIO_PIN_10
#define RXD_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
