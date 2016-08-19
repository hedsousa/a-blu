#ifndef __UTILS_H
#define __UTILS_H
#include "main.h"



/* LCD typedef -------------------------------------------------------------*/
typedef enum LCD_States {LCD_ON, LCD_OFF} LCD_State;

/* LCD Functions -----------------------------------------------------------*/
void LCD_Startup_Config(void);
void LCD_State_Control(void); 
void LCD_PrintError(char* errorMessage);

/* EEPROM typedef -------------------------------------------------------------*/
#define EEPROM_BUFFER_SIZE    64
#define EEPROM_WRITE_ADDRESS1 0x50
#define EEPROM_READ_ADDRESS1  0x50

/* EEPROM Functions --------------------------------------------------------*/
void EEPROM_Init(void);
void EEPROM_Write(uint8_t* w_buffer);
void EEPROM_Read(uint8_t* r_buffer);

#endif
