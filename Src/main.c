/**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @version V1.2.4
  * @date    06-May-2016
  * @brief   Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
BD_ADDR_t Bd_Addr_Test;
Link_Key_t Link_Key_Test;
LinkKeyInfo_t LinkKey_Str_Test;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
void LCD_PrintMessageAtLine(uint8_t* message, int line, int color);

/* Private functions ---------------------------------------------------------*/

void LCD_PrintMessageAtLine(uint8_t* message, int line, int color){
	BSP_LCD_Clear(color);
	BSP_LCD_DisplayStringAtLine(line, message);
}

static void LCD_Init(){
	BSP_LCD_Init();
	BSP_LCD_Clear(LCD_COLOR_GREEN);
	BSP_LCD_DisplayOff();
	BSP_LCD_DisplayOn();
	BSP_LCD_DisplayStringAtLine(4,(uint8_t*)"DEBUG");
}

void PrepareTestKeys(){
	ASSIGN_BD_ADDR(Bd_Addr_Test, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08);
	ASSIGN_LINK_KEY(Link_Key_Test, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08 );
}

void KeyLogger_Tests(void){
	bool status = true;
	
	KeyLogger_Init();       /* Inicia a EEPROM e carrega a estrutura de dados */
	//Add
	status = KeyLogger_Add(Bd_Addr_Test, Link_Key_Test);
	
	//Exists
	status = KeyLogger_Exists(Bd_Addr_Test);
			
	//Get
	status = KeyLogger_Get(Bd_Addr_Test,&LinkKey_Str_Test);

	//Remove
	status = KeyLogger_Remove(Bd_Addr_Test);
	
	//Exists
	status = KeyLogger_Exists(Bd_Addr_Test);
	
	//Add Str_test
	status = KeyLogger_Add(LinkKey_Str_Test.BD_ADDR, LinkKey_Str_Test.LinkKey);
	
	//Clear
	KeyLogger_Clear();
	
	status = KeyLogger_Exists(LinkKey_Str_Test.BD_ADDR);
	
	//Add
	status = KeyLogger_Add(Bd_Addr_Test, Link_Key_Test);
	
	status = KeyLogger_Exists(LinkKey_Str_Test.BD_ADDR);

	//Power off
	//repete...
}


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  HAL_Init();
  SystemClock_Config();  /* Configure the system clock to 168 MHz */
	LCD_Init();
	KeyLogger_Tests();
	
	/*Teste GPIO toggle*/
  __HAL_RCC_GPIOG_CLK_ENABLE();		
	GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_InitStruct.Pin = (GPIO_PIN_6);
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  while (1)
  {
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
    HAL_Delay(100);
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
