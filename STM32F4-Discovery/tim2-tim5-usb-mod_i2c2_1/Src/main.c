/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define I2C2_ADDRESS		0x14
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim8;

/* USER CODE BEGIN PV */
char RawFreq[80];
char TIM2CNTBUF[80];
volatile unsigned int i2c_ram[8];
//volatile unsigned int i2c_ram[8]={0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x0a};
unsigned int test_register[40];
uint8_t I2C_data_buff_RX[1];
uint16_t I2C_buff_size;
uint8_t I2C_data_buff_TX[1];

unsigned int freqTIM2Before=0;
 unsigned int freqTIM2After=0;
volatile unsigned int freqTIM2PerSecond=0;

 unsigned int freqTIM5Before=0;
 unsigned int freqTIM5After=0;
volatile unsigned int freqTIM5PerSecond=0;

 unsigned int GENcount=0;
 unsigned int x=0, x1=0, x2=0, x3=0, x4=0;
 unsigned int y=0,  y2=0, y3=0, y4=0;
 unsigned int y1=0;
/* USER CODE END PV */


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM5_Init(void);
static void MX_I2C2_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM8_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

        if(htim->Instance == TIM1) //check if the interrupt comes from TIM1
        {
        	freqTIM2After=TIM2->CNT;
        			freqTIM2PerSecond=freqTIM2After-freqTIM2Before;
        			freqTIM2PerSecond-=freqTIM2PerSecond*0.00095;
        			freqTIM5After=TIM5->CNT;
        		    freqTIM5PerSecond=freqTIM5After-freqTIM5Before;
        		    freqTIM5PerSecond-=freqTIM5PerSecond*0.00095;

        		/*    x=TIM2->CNT;//freqTIM2PerSecond;
        		 	    x4 = x&0x000000FF;
        		 	    x3 = (x&0x0000FF00) >> 8;
        		 	    x2 = (x&0x00FF0000) >> 16;
        		 	    x1 = (x&0xFF000000) >> 24;

        		 	    y=TIM5->CNT;//freqTIM5PerSecond;
        		 	   	y4 = y&0x000000FF;
        		 	   	y3 = (y&0x0000FF00) >> 8;
        		 	   	y2 = (y&0x00FF0000) >> 16;
        		 	   	y1 = (y&0xFF000000) >> 24;

        		 	   	i2c_ram[0]=x1;
        		 	    i2c_ram[1]=x2;
        		 	   	i2c_ram[2]=x3;
        		 	   	i2c_ram[3]=x4;
        		 	   	i2c_ram[4]=y1;
        		 	   	i2c_ram[5]=y2;
        		 	   	i2c_ram[6]=y3;
        		 	   	i2c_ram[7]=y4;*/
        		 	   sprintf(RawFreq, "%u \t %u \t %u \r\n", GENcount, freqTIM2PerSecond, freqTIM5PerSecond);
        		 	   CDC_Transmit_FS((uint8_t *)RawFreq, 80);
        		 	    freqTIM2Before=freqTIM2After;
        		 	 	freqTIM5Before=freqTIM5After;
        		 	 	GENcount++; if(GENcount > 4000000000){GENcount = 0;}
        }
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
  MX_TIM2_Init();
  MX_TIM5_Init();
  MX_USB_DEVICE_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
  TIM2->CR1     |= TIM_CR1_CEN;//1: Counter enabled
  TIM2->EGR |= TIM_EGR_UG;

  TIM5->CR1     |= TIM_CR1_CEN;//1: Counter enabled
  TIM5->EGR |= TIM_EGR_UG;

  TIM8->CR1     |= TIM_CR1_CEN;//1: Counter enabled
  TIM8->EGR |= TIM_EGR_UG;

  TIM1->CR1		|= TIM_CR1_CEN;
  TIM1->EGR |= TIM_EGR_UG;

  I2C2->CR2     |= I2C_CR2_FREQ_3; //0b01000: 8 MHz Peripheral Clock Frequency == 8 MHz!
  /*I2C2->CCR     |= 0x28;           // clock control register (270kHz)?!
  I2C2->TRISE   |= 0x09;          // rise time register*/
  I2C2->CR1 	|= I2C_CR1_PE;     //1:  Peripheral enable




  HAL_TIM_Base_Start_IT(&htim1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


//  I2C2_EV_IRQHandler();


  while (1)
  {
	  	  	x=freqTIM2PerSecond;
	 	    x4 = x&0x000000FF;
	 	    x3 = (x&0x0000FF00) >> 8;
	 	    x2 = (x&0x00FF0000) >> 16;
	 	    x1 = (x&0xFF000000) >> 24;

	 	    y=freqTIM5PerSecond;
	 	   	y4 = y&0x000000FF;
	 	   	y3 = (y&0x0000FF00) >> 8;
	 	   	y2 = (y&0x00FF0000) >> 16;
	 	   	y1 = (y&0xFF000000) >> 24;

	 	   	i2c_ram[0]=x1;
	 	    i2c_ram[1]=x2;
	 	   	i2c_ram[2]=x3;
	 	   	i2c_ram[3]=x4;
	 	   	i2c_ram[4]=y1;
	 	   	i2c_ram[5]=y2;
	 	   	i2c_ram[6]=y3;
	 	   	i2c_ram[7]=y4;
		/*freqTIM2After=TIM2->CNT;
		freqTIM2PerSecond=freqTIM2After-freqTIM2Before;
		freqTIM2PerSecond-=freqTIM2PerSecond*0.00095;
		freqTIM5After=TIM5->CNT;
	    freqTIM5PerSecond=freqTIM5After-freqTIM5Before;
	    freqTIM5PerSecond-=freqTIM5PerSecond*0.00095;*/

	    I2C2->CR1		|=I2C_CR1_ACK; //A
	  //  if(!(I2C2->SR1 & I2C_SR1_ADDR)){
	    while (!(I2C2->SR1 & I2C_SR1_ADDR)){}; //ev1
	    I2C2->SR1;
	    I2C2->SR2;
	    while (!(I2C2->SR1 & I2C_SR1_TXE)){}; //ev3-1 */

	   	/*while((I2C2->SR1 & I2C_SR1_ADDR) == I2C_SR1_ADDR){
	      I2C2->SR1;
	      I2C2->SR2;
	    }*/


	  /* I2C2->DR = x1; //data1
	   while (!(I2C2->SR1 & I2C_SR1_TXE)){}; //ev3
	   I2C2->CR1		|=I2C_CR1_ACK;
	   I2C2->DR = x2; //data2
	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
	   I2C2->CR1		|=I2C_CR1_ACK;
	   I2C2->DR = x3; //data3
	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
	   I2C2->CR1		|=I2C_CR1_ACK;
	   I2C2->DR = x4; //data4
	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
	   I2C2->CR1		|=I2C_CR1_ACK;
	   I2C2->DR = y1; //data5
	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
	   I2C2->CR1		|=I2C_CR1_ACK;
	   I2C2->DR = y2; //data6
	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
	   I2C2->CR1		|=I2C_CR1_ACK;
	   I2C2->DR = y3; //data7
	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3
	   I2C2->CR1		|=I2C_CR1_ACK;
	   I2C2->DR = y4; //data8
	   while (!(I2C2->SR1 & I2C_SR1_TXE)){};  //ev3 */
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
	      	   HAL_Delay(1);
	//    }
	 //   else{}
//	    sprintf(TIM2CNTBUF, "%u \t \%x \t %u  \t %u  \t %u  \t %u  \t %u  \t %u \r\n", GENcount, (unsigned int)I2C2->OAR1,(unsigned int)(y1), (unsigned int)(y2), (unsigned int)(y3), (unsigned int)(y4),  (unsigned int)(y5), (unsigned int)TIM2->CNT);
	 /*  sprintf(RawFreq, "%u \t %u \t %u \r\n", GENcount, freqTIM2PerSecond, freqTIM5PerSecond);
	   CDC_Transmit_FS((uint8_t *)RawFreq, 80);
	   freqTIM2Before=freqTIM2After;
	   freqTIM5Before=freqTIM5After;


	   HAL_Delay(1000);
	   GENcount++;*/


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void I2C_Transmit_Handler(unsigned int i2c_ram[8]){
	//if(hi2c2.State == HAL_I2C_STATE_READY){
		//	if(!(I2C2->SR1 & I2C_SR1_ADDR)){
	  I2C2->CR1		|=I2C_CR1_ACK; //A

	//  if(hi2c2.State == HAL_I2C_STATE_BUSY_TX_LISTEN){
		 // while(!(I2C2->SR1 & I2C_SR1_ADDR)){}
	  if(hi2c2.State == HAL_I2C_STATE_READY){

	//  I2C2->CR1		|=I2C_CR1_ACK; //A
	  while (!(I2C2->SR1 & I2C_SR1_ADDR)){}; //ev1

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
	  	 I2C1 -> CR1 |= I2C_CR1_STOP;
	  }
		//}
			else {}
}




/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 134;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_ENABLE; //I2C_NOSTRETCH_ENABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 8399;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 10000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0xFFFFFFFF;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  sSlaveConfig.InputTrigger = TIM_TS_TI2FP2;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 0xFFFFFFFF;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchro(&htim5, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim5, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */
  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 839;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 50000;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : PD12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 */
   GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
   GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
   GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
