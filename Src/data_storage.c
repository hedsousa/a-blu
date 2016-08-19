#include "data_storage.h"
// Este modulo deveria chamar-se data_storage_eeprom.c. Deveria ter outro modulo chamado
// data_storage onde defenia qual o tipo de storage a usar, se eeprom ou sd e assim nao
///mudava as funcoes que dependiam deste

//#define DATA_STORAGE_PRINT_ERROR /* Usar se definidas funcoes para o lcd. (Foram definidas em modulos anteriores, mas para o projeto final escolhi nao incluir)*/

void LCD_PrintError(char* errorMessage){
	BSP_LCD_Clear(LCD_COLOR_RED);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);
	BSP_LCD_DisplayStringAtLine(2, (uint8_t*)"Erro na funcao:");	
  BSP_LCD_DisplayStringAtLine(3, (uint8_t*)errorMessage);
}

void DataStorage_PrintError(uint32_t curr_status, uint32_t cmp_status, char* message){
#ifdef DATA_STORAGE_PRINT_ERROR
	if( curr_status != cmp_status){
		LCD_PrintError(message);
	}
#endif
}


uint32_t DataStorage_Init(){
	uint32_t status = EEPROM_OK;
	//uint32_t x = 0;
	  /* Select the EEPROM address and check if OK */
//  if(EEPROM_IO_IsDeviceReady(EEPROM_I2C_ADDRESS, EEPROM_MAX_TRIALS) != HAL_OK)
//  {
//    x = 1;
//  }
	
	status = BSP_EEPROM_Init();
#ifdef DATA_STORAGE_PRINT_ERROR	
	DataStorage_PrintError(status, EEPROM_OK, "DataStorage_Init()");
#endif
	return status;
}


uint32_t DataStorage_Save(uint16_t offset, void* data_ptr, uint16_t size){
	uint16_t effective_addr = EEPROM_START_ADDR;
	uint32_t status = EEPROM_OK;
	
	//escrever o "size" na eeprom  
	effective_addr += offset;
	status = BSP_EEPROM_WriteBuffer((uint8_t*)&size, effective_addr, sizeof(uint16_t));
	if(status != EEPROM_OK){
#ifdef DATA_STORAGE_PRINT_ERROR	
		DataStorage_PrintError(status, EEPROM_OK, "DataStorage_Save size");
#endif
		return status;
	}
	
	//guardar o buffer com a dimensao passada, na posicao offset+2
	effective_addr += sizeof(uint16_t);
	status = BSP_EEPROM_WriteBuffer((uint8_t*)data_ptr, effective_addr, size);
	if(status != EEPROM_OK){
#ifdef DATA_STORAGE_PRINT_ERROR			
		DataStorage_PrintError(status, EEPROM_OK, "DataStorage_Save data");
#endif		
		return status;
	}
	return status;
}


uint32_t DataStorage_Load(uint16_t offset, void* data_ptr){
	uint16_t effective_addr = EEPROM_START_ADDR;
	uint16_t data_size = 0;
	uint16_t n_bytes_read;
	uint32_t status = EEPROM_OK;
	
	//ler o size em offset (2 bytes)
	effective_addr += offset;
	n_bytes_read = sizeof(uint16_t);
	status = BSP_EEPROM_ReadBuffer((uint8_t*)&data_size, effective_addr, &n_bytes_read);
	if(status != EEPROM_OK){
#ifdef DATA_STORAGE_PRINT_ERROR	
		DataStorage_PrintError(status, EEPROM_OK, "DataStorage_Load size");
#endif
		return status;
	}
	
	
	//comecando em offset+2 ler para o data_ptr "size" bytes
	effective_addr += sizeof(uint16_t);
	status = BSP_EEPROM_ReadBuffer((uint8_t*)data_ptr, effective_addr, &data_size);
	if(status != EEPROM_OK){
#ifdef DATA_STORAGE_PRINT_ERROR	
		DataStorage_PrintError(status, EEPROM_OK, "DataStorage_Load size");
#endif
	return status;
	}
	return status;
}
