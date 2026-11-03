#include "flash_helper.h"
#include "stm32f4xx_conf.h"
#include <string.h>
#include "ucos_ii.h"  		// uC/OS-II系统函数头文件
#include "os_cpu.h"
/*
 * 定义
 */
#define FLASH_SECTORS				12
#define BOOTLOADER_BASE			11
#define APP_BASE						0
#define NEW_APP_BASE				8
#define NEW_APP_SECTORS			3

// Flash 扇区基地址
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) // Base @ of Sector 0, 16 Kbytes
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) // Base @ of Sector 1, 16 Kbytes
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) // Base @ of Sector 2, 16 Kbytes
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) // Base @ of Sector 3, 16 Kbytes
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) // Base @ of Sector 4, 64 Kbytes
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) // Base @ of Sector 5, 128 Kbytes
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) // Base @ of Sector 6, 128 Kbytes
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) // Base @ of Sector 7, 128 Kbytes
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) // Base @ of Sector 8, 128 Kbytes
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) // Base @ of Sector 9, 128 Kbytes
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) // Base @ of Sector 10, 128 Kbytes
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) // Base @ of Sector 11, 128 Kbytes

// 私有变量
static const uint32_t flash_addr[FLASH_SECTORS] = {
		ADDR_FLASH_SECTOR_0,
		ADDR_FLASH_SECTOR_1,
		ADDR_FLASH_SECTOR_2,
		ADDR_FLASH_SECTOR_3,
		ADDR_FLASH_SECTOR_4,
		ADDR_FLASH_SECTOR_5,
		ADDR_FLASH_SECTOR_6,
		ADDR_FLASH_SECTOR_7,
		ADDR_FLASH_SECTOR_8,
		ADDR_FLASH_SECTOR_9,
		ADDR_FLASH_SECTOR_10,
		ADDR_FLASH_SECTOR_11
};
static const uint16_t flash_sector[FLASH_SECTORS] = {
		FLASH_Sector_0,
		FLASH_Sector_1,
		FLASH_Sector_2,
		FLASH_Sector_3,
		FLASH_Sector_4,
		FLASH_Sector_5,
		FLASH_Sector_6,
		FLASH_Sector_7,
		FLASH_Sector_8,
		FLASH_Sector_9,
		FLASH_Sector_10,
		FLASH_Sector_11
};

uint16_t flash_helper_erase_new_app(uint32_t new_app_size) {
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
			FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	new_app_size += flash_addr[NEW_APP_BASE];

	OSSchedLock();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, DISABLE);

	for (int i = 0;i < NEW_APP_SECTORS;i++) {
		if (new_app_size > flash_addr[NEW_APP_BASE + i]) {
			uint16_t res = FLASH_EraseSector(flash_sector[NEW_APP_BASE + i], VoltageRange_3);
			if (res != FLASH_COMPLETE) {
				return res;
			}
		} else {
			break;
		}
	}

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	OSSchedUnlock();
	
	return FLASH_COMPLETE;
}

uint16_t flash_helper_erase_new_bootloader(uint32_t new_bootloader_size) {
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
			FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	new_bootloader_size += flash_addr[BOOTLOADER_BASE];

	OSSchedLock();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, DISABLE);

		if (new_bootloader_size > flash_addr[BOOTLOADER_BASE]) {
			uint16_t res = FLASH_EraseSector(flash_sector[BOOTLOADER_BASE], VoltageRange_3);
			if (res != FLASH_COMPLETE) {
				return res;
			}
		} else {
		}

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	OSSchedUnlock();
	
	return FLASH_COMPLETE;
}

uint16_t flash_helper_write_new_app_data(uint32_t offset, uint8_t *data, uint32_t len) {
	FLASH_ClearFlag(FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
			FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	OSSchedLock();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, DISABLE);

	for (uint32_t i = 0;i < len;i++) {
		uint16_t res = FLASH_ProgramByte(flash_addr[NEW_APP_BASE] + offset + i, data[i]);
		if (res != FLASH_COMPLETE) {
			return res;
		}
	}

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	OSSchedUnlock();

	return FLASH_COMPLETE;
}

uint16_t flash_helper_write_new_bootloader_data(uint32_t offset, uint8_t *data, uint32_t len) {
	FLASH_ClearFlag(FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
			FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	OSSchedLock();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, DISABLE);

	for (uint32_t i = 0;i < len;i++) {
		uint16_t res = FLASH_ProgramByte(flash_addr[BOOTLOADER_BASE] + offset + i, data[i]);
		if (res != FLASH_COMPLETE) {
			return res;
		}
	}

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	OSSchedUnlock();

	return FLASH_COMPLETE;
}

/*
 * 停止系统运行并跳转到bootloader
 */
void flash_helper_jump_to_bootloader(void) {
	typedef void (*pFunction)(void);

	//禁止CAN通信和串口通信
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);                   //使能GPIOB时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);                   //使能GPIOD时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;  //CAN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                            //普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                      //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                            //上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);                                  //初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  //串口1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                            //普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                      //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                            //上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);                                  //初始化GPIO

	// 禁止watchdog
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, DISABLE);

	//此处需测试 关闭全部中断
	OSIntEnter();
	
	pFunction jump_to_bootloader;

	// 加载bootloader的起始地址变量
	volatile uint32_t* jump_address;
	const volatile uint32_t* bootloader_address = (volatile uint32_t*)0x080E0000;

	// 获取bootloader向量表
	jump_address = (volatile uint32_t*) bootloader_address[1];

	// 加载地址到函数指针
	jump_to_bootloader = (pFunction) jump_address;

	// 清除挂起中断
	SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk;

	// 禁止全部中断
	for(int i = 0;i < 8;i++) {
		NVIC->ICER[i] = NVIC->IABR[i];
	}

	// 设置栈指针
	__set_MSP((uint32_t) (bootloader_address[0]));

	// 跳转到bootloader
	jump_to_bootloader();
}

uint8_t* flash_helper_get_sector_address(uint32_t fsector) {
	uint8_t *res = 0;

	for (int i = 0;i < FLASH_SECTORS;i++) {
		if (flash_sector[i] == fsector) {
			res = (uint8_t *)flash_addr[i];
			break;
		}
	}

	return res;
}
