#ifndef __DATA_STORAGE_H
#define __DATA_STORAGE_H
#include "stm324xg_eval_eeprom.h"
#include "utils.h"

#define EEPROM_START_ADDR 0

uint32_t DataStorage_Init(void);
uint32_t DataStorage_Save(uint16_t offset, void* data_ptr, uint16_t size);
uint32_t DataStorage_Load(uint16_t offset, void* data_ptr);

#endif
