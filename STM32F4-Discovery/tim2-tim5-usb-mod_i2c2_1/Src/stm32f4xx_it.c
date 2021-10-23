/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_i2c.h"

#include "usbd_cdc_if.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */
#define FLAG_MASK         ((uint32_t)0x00FFFFFF)  /*<! I2C FLAG mask */
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
char RawFreq[80];
uint32_t I2C_data_buff_RX;
	uint16_t I2C_buff_size;
	uint8_t I2C_data_buff_TX[1];
	extern  volatile unsigned int i2c_ram[8];
//	unsigned int i2c_ram[8]={0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x0a};
	extern volatile unsigned int GENcount;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
extern I2C_HandleTypeDef hi2c2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;


/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */

void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
  * @brief This function handles I2C2 event interrupt.
  */



uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0, flag2 = 0;

  // Check the parameters
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  // Read the I2Cx status register
  flag1 = I2Cx->SR1;
  flag2 = I2Cx->SR2;
  flag2 = flag2 << 16;

  // Get the last event value from I2C status register
  lastevent = (flag1 | flag2) & FLAG_MASK;

   //Return status
  return lastevent;
}


void I2C2_EV_IRQHandler(void);
void I2C2_EV_IRQHandler(void)
{
  /* USER CODE BEGIN I2C2_EV_IRQn 0 */
  /* USER CODE END I2C2_EV_IRQn 0 */

  HAL_I2C_EV_IRQHandler(&hi2c2);\


	//if(hi2c2.State == HAL_I2C_STATE_READY){
		if(!(I2C2->SR1 & I2C_SR1_ADDR)){
  I2C2->CR1		|=I2C_CR1_ACK; //A

//  if(hi2c2.State == HAL_I2C_STATE_BUSY_TX_LISTEN){
	 // while(!(I2C2->SR1 & I2C_SR1_ADDR)){}

  /* USER CODE BEGIN I2C2_EV_IRQn 1 */

//  I2C2->CR1		|=I2C_CR1_ACK; //A
  while (!(I2C2->SR1 & I2C_SR1_ADDR)){}; //ev1
//	if(I2C_FLAG_ADDR==1){
  I2C2->SR1;
  I2C2->SR2;
  I2C2->CR1		|=I2C_CR1_ACK; //A
  while (!(I2C2->SR1 & I2C_SR1_TXE)){}; //ev2
	//}

  	   I2C2->DR = i2c_ram[0]; //data1
  	   while (!(I2C2->SR1 & I2C_SR1_TXE)){}; //ev3
  	  // while (!(I2C2->SR1 & I2C_SR1_BTF)){};
  	 //  I2C2->CR1		|=I2C_CR1_ACK;
  	   I2C2->DR = i2c_ram[1]; //data2
  	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
  	  // while (!(I2C2->SR1 & I2C_SR1_BTF)){};
  	//   I2C2->CR1		|=I2C_CR1_ACK;
  	   I2C2->DR = i2c_ram[2]; //data3
  	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
  	  // while (!(I2C2->SR1 & I2C_SR1_BTF)){};
  	//   I2C2->CR1		|=I2C_CR1_ACK;
  	   I2C2->DR = i2c_ram[3]; //data4
  	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
  	//   while (!(I2C2->SR1 & I2C_SR1_BTF)){};

  	  // I2C2->SR1 &= ~I2C_SR1_AF;

  	   //HAL_I2C_Slave_Transmit(&hi2c2, &i2c_ram, 8,1000);
  	 //while((I2C2->SR1 & I2C_SR1_TIMEOUT)){}



  	   //   I2C2->CR1		|=I2C_CR1_ACK;
  	   I2C2->DR = i2c_ram[4]; //data5
  	  while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
  	//   I2C2->CR1		|=I2C_CR1_ACK;
  	   I2C2->DR = i2c_ram[5]; //data6
  	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
  	//   I2C2->CR1		|=I2C_CR1_ACK;
  	   I2C2->DR = i2c_ram[6]; //data7
  	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
  	//   I2C2->CR1		|=I2C_CR1_ACK;
  	   I2C2->DR = i2c_ram[7]; //data8
  	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3

	}
  I2C1 -> CR1 |= I2C_CR1_STOP;
 // }

        //sprintf(RawFreq, "%u \t %lu \t %u \t %u \r\n", GENcount, I2C_data_buff_RX, i2c_ram[0], i2c_ram[1]);
                 //sprintf(RawFreq, "%u \t %u \t %u \r\n", GENcount, freqTIM2PerSecond, freqTIM5PerSecond);
          //CDC_Transmit_FS((uint8_t *)RawFreq, 80);
  /* USER CODE END I2C2_EV_IRQn 1 */
}

void I2C_my_Handler(void)
{
}
/**
  * @brief This function handles I2C2 error interrupt.
  */
void I2C2_ER_IRQHandler(void)
{
  /* USER CODE BEGIN I2C2_ER_IRQn 0 */

  /* USER CODE END I2C2_ER_IRQn 0 */
  HAL_I2C_ER_IRQHandler(&hi2c2);
  /* USER CODE BEGIN I2C2_ER_IRQn 1 */

  /* USER CODE END I2C2_ER_IRQn 1 */
}

/**
  * @brief This function handles TIM8 update interrupt and TIM13 global interrupt.
  */
void TIM8_UP_TIM13_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_UP_TIM13_IRQn 0 */

  /* USER CODE END TIM8_UP_TIM13_IRQn 0 */
  HAL_TIM_IRQHandler(&htim8);
  /* USER CODE BEGIN TIM8_UP_TIM13_IRQn 1 */

  /* USER CODE END TIM8_UP_TIM13_IRQn 1 */
}

/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
