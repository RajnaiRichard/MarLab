/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define RightButtonEN_Pin GPIO_PIN_14
#define RightButtonEN_GPIO_Port GPIOC
#define LeftButtonEN_Pin GPIO_PIN_15
#define LeftButtonEN_GPIO_Port GPIOC
#define LeftButton_Pin GPIO_PIN_2
#define LeftButton_GPIO_Port GPIOC
#define RightButton_Pin GPIO_PIN_3
#define RightButton_GPIO_Port GPIOC
#define LCD_EN_Pin GPIO_PIN_1
#define LCD_EN_GPIO_Port GPIOA
#define LCD_CS1_Pin GPIO_PIN_2
#define LCD_CS1_GPIO_Port GPIOA
#define LCD_CS2_Pin GPIO_PIN_3
#define LCD_CS2_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_6
#define LCD_RST_GPIO_Port GPIOA
#define LCD_RW_Pin GPIO_PIN_7
#define LCD_RW_GPIO_Port GPIOA
#define LCD_DI_Pin GPIO_PIN_1
#define LCD_DI_GPIO_Port GPIOB
#define LCD_DB7_Pin GPIO_PIN_10
#define LCD_DB7_GPIO_Port GPIOB
#define LCD_K_Pin GPIO_PIN_12
#define LCD_K_GPIO_Port GPIOB
#define LCD_E_Pin GPIO_PIN_8
#define LCD_E_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define LCD_DB0_Pin GPIO_PIN_3
#define LCD_DB0_GPIO_Port GPIOB
#define LCD_DB1_Pin GPIO_PIN_4
#define LCD_DB1_GPIO_Port GPIOB
#define LCD_DB2_Pin GPIO_PIN_5
#define LCD_DB2_GPIO_Port GPIOB
#define LCD_DB3_Pin GPIO_PIN_6
#define LCD_DB3_GPIO_Port GPIOB
#define LCD_DB4_Pin GPIO_PIN_7
#define LCD_DB4_GPIO_Port GPIOB
#define LCD_DB5_Pin GPIO_PIN_8
#define LCD_DB5_GPIO_Port GPIOB
#define LCD_DB6_Pin GPIO_PIN_9
#define LCD_DB6_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
