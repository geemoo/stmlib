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
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
	uint32_t AHBRSTR;
	uint32_t CFGR2;
	uint32_t CFGR3;
	uint32_t CR2;
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
