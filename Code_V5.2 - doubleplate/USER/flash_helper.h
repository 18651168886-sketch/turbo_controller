#ifndef FLASH_HELPER_H_
#define FLASH_HELPER_H_

#include "stm32f4xx.h"

// Functions
uint16_t flash_helper_erase_new_app(uint32_t new_app_size);
uint16_t flash_helper_erase_new_bootloader(uint32_t new_bootloader_size);
uint16_t flash_helper_write_new_app_data(uint32_t offset, uint8_t *data, uint32_t len);
uint16_t flash_helper_write_new_bootloader_data(uint32_t offset, uint8_t *data, uint32_t len);
void flash_helper_jump_to_bootloader(void);
uint8_t* flash_helper_get_sector_address(uint32_t fsector);

#endif /* FLASH_HELPER_H_ */
