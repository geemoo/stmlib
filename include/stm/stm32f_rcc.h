#ifndef __STM32F_RCC_H__
#define __STM32F_RCC_H__

#define RCC_GPIOA 0x00020000
#define RCC_GPIOB 0x00040000
#define RCC_GPIOC 0x00080000
#define RCC_GPIOD 0x00100000
#define RCC_GPIOE 0x00200000
#define RCC_GPIOF 0x00400000

/*
 * declare structs
 */

struct stm_rcc_dev {
	uint32_t cr;
	uint32_t cfgr;
	uint32_t cir;
	uint32_t apb2rstr;
	uint32_t apb1rstr;
	uint32_t ahbenr;
	uint32_t apb2enr;
	uint32_t apb1enr;
	uint32_t bdcr;
	uint32_t csr;
	uint32_t ahbrstr;
	uint32_t cfgr2;
	uint32_t cfgr3;
	uint32_t cr2;
};


/*
 * define hardware aliases
 */
#define RCC ((struct stm_rcc_dev *) (0x40021000))


/* 
 * function defines
 */
uint32_t stm_rcc_enable(uint32_t clock, uint32_t state);

#endif
