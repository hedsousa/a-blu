#include "utils.h"


/* LCD variables -----------------------------------------------------------*/
 LCD_State LCD_last_state = LCD_ON;

/* EEPROM variables -----------------------------------------------------------*/

__IO uint16_t NumDataRead = EEPROM_BUFFER_SIZE;

/* LCD Functions -----------------------------------------------------------*/
/*
static void LCD_Init(){
	BSP_LCD_Init();
	BSP_LCD_Clear(LCD_COLOR_GREEN);
	BSP_LCD_DisplayOff();
	BSP_LCD_DisplayOn();
	#ifdef LCD_RELEASE // Macro definida em lcd_image.h
		BSP_LCD_DrawRGBImage(0,0,320,240,(uint8_t*)LCD_IMAGE);
	#else
		BSP_LCD_DisplayStringAtLine(4,(uint8_t*)LCD_Message);
	#endif
}

*/

static void EXTI_PA0pin_config(){
	GPIO_InitTypeDef gpio_str;
	
	__HAL_RCC_GPIOA_CLK_ENABLE(); 
	
	gpio_str.Mode = GPIO_MODE_IT_RISING;
	gpio_str.Pull = GPIO_NOPULL;
	gpio_str.Pin	= GPIO_PIN_0;
	HAL_GPIO_Init(GPIOA, &gpio_str);
	
	HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void LCD_Startup_Config(){
	EXTI_PA0pin_config();
  BSP_LED_Init(LED2);
	LCD_Init(); 	
//errorHandling = LCD_ErrorHandling;

}

void LCD_State_Control(){
   
	if(LCD_last_state == LCD_ON){
	
		BSP_LCD_DisplayOff();
		BSP_LED_On(LED2);
		LCD_last_state = LCD_OFF;
		
	}else{
		
		BSP_LCD_DisplayOn();
		BSP_LED_Off(LED2);
		LCD_last_state = LCD_ON;
	}
}
	
void LCD_PrintError(char* errorMessage){
	BSP_LCD_Clear(LCD_COLOR_RED);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);
	BSP_LCD_DisplayStringAtLine(2, (uint8_t*)"Erro na funcao:");	
  BSP_LCD_DisplayStringAtLine(3, (uint8_t*)errorMessage);
}


/* EEPROM Functions -----------------------------------------------------------*/

//void EEPROM_Init(){
//	if(BSP_EEPROM_Init() != EEPROM_OK)
//  {
//		BSP_LCD_Clear(LCD_COLOR_RED);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);    
//    BSP_LCD_DisplayStringAt(0, 115, (uint8_t *)"Initialization Issue", CENTER_MODE);
//  }
//}

//void EEPROM_Write(uint8_t* w_buffer){
//	
//    /* Write on I2C EEPROM to EEPROM_WRITE_ADDRESS1 */
//    if(BSP_EEPROM_WriteBuffer(w_buffer, EEPROM_WRITE_ADDRESS1, EEPROM_BUFFER_SIZE) != EEPROM_OK)
//    {
//     	BSP_LCD_Clear(LCD_COLOR_RED);
//			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);    
//      BSP_LCD_DisplayStringAt(0, 115, (uint8_t *)"issue at write", CENTER_MODE);
//    }
//}

//void EEPROM_Read(uint8_t* r_buffer){
// /* Read from I2C EEPROM from EEPROM_READ_ADDRESS1 */
//	if(BSP_EEPROM_ReadBuffer(r_buffer, EEPROM_READ_ADDRESS1, (uint16_t *)(&NumDataRead)) != EEPROM_OK)
//  {
//		BSP_LCD_Clear(LCD_COLOR_RED);
//    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);     
//		BSP_LCD_DisplayStringAt(0, 115, (uint8_t *)"Init issue at read", CENTER_MODE);
//	}
//}
