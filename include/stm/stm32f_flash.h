#ifndef __STM32F_FLASH_H__
#define __STM32F_FLASH_H__

#include <stdint.h>


/*
 * define constants
 */

/// FLASH->ACR
#define BP_ACR_LATENCY 0
#define MASK_ACR_LATENCY 0x00000007
#define BP_ACR_PRFTBE 4
#define BP_ACR_PRFTBS 5


/*
 * declare structs
 */

struct stm_flash_dev {
	uint32_t ACR;
	uint32_t KEYR;
	uint32_t OPTKEYR;
	uint32_t SR;
	uint32_t CR;
	uint32_t AR;
	uint32_t OBR;
	uint32_t WRPR;
};


/*
 * define hardware aliases
 */
#define FLASH ((struct stm_flash_dev *) (0x40022000))


/* 
 * function defines
 */


#endif
