#ifndef __STM32F_RCC_H__
#define __STM32F_RCC_H__

#include <stdint.h>


/*
 * define constants
 */

/// default HSI value
#ifndef HSI_VALUE
#define HSI_VALUE 8000000
#endif

/// default HSE value
#ifndef HSE_VALUE
#define HSE_VALUE 8000000
#endif

/// constants to be used with stm_rcc_enable()
#define RCC_GPIOA ((1 << 30) | (1 << 29) | (1 << 1))
#define RCC_GPIOB ((1 << 30) | (1 << 29) | (1 << 2))
#define RCC_GPIOC ((1 << 30) | (1 << 29) | (1 << 3))
#define RCC_GPIOD ((1 << 30) | (1 << 29) | (1 << 4))
#define RCC_GPIOE ((1 << 30) | (1 << 29) | (1 << 5))
#define RCC_GPIOF ((1 << 30) | (1 << 29) | (1 << 6))

/// RCC->CR
#define BP_CR_HSION 0
#define BP_CR_HSIRDY 1
#define BP_CR_HSITRIM 2
#define MASK_CR_HSITRIM 0x0000001f
#define BP_CR_HSICAL 8
#define MASK_CR_HSICAL 0x000000ff
#define BP_CR_HSEON 16
#define BP_CR_HSERDY 17
#define BP_CR_HSEBYP 18
#define BP_CR_CSSON 19
#define BP_CR_PLLON 24
#define BP_CR_PLLRDY 25

/// RCC->CFGR
#define MASK_CFGR_SW 0x00000003
#define BP_CFGR_SW 0
#define MASK_CFGR_SWS 0x00000003
#define BP_CFGR_SWS 2
#define MASK_CFGR_HPRE 0x0000000f
#define BP_CFGR_HPRE 4
#define MASK_CFGR_PPRE 0x00000007
#define BP_CFGR_PPRE 8
#define BP_CFGR_ADCPRE 14
#define MASK_CFGR_PLLSRC 0x00000003
#define BP_CFGR_PLLSRC 15
#define BP_CFGR_PLLXTPRE 17
#define MASK_CFGR_PLLMUL 0x0000000f
#define BP_CFGR_PLLMUL 18
#define MASK_CFGR_MCO 0x0000000f
#define BP_CFGR_MCO 24
#define MASK_CFGR_MCOPRE 0x00000007
#define BP_CFGR_MCOPRE 28
#define BP_CFGR_PLLNODIV 31

/// RCC->CFGR2
#define BP_CFGR2_PREDIV 0
#define MASK_CFGR2_PREDIV 0x0000000f

/// RCC->CFGR3
#define BP_CFGR3_USART1SW 0
#define MASK_CFGR3_USART1SW 0x00000003
#define BP_CFGR3_I2C1SW 4
#define BP_CFGR3_CECSW 6
#define BP_CFGR3_USBSW 7
#define BP_CFGR3_ADC1SW 8
#define BP_CFGR3_USART2SW 16
#define MASK_CFGR3_USART2SW 0x00000003
#define BP_CFGR3_USART3SW 18
#define MASK_CFGR3_USART3SW 0x00000003

/// RCC->CR2
#define BP_CR2_HSI14ON 0
#define BP_CR2_HSI14RDY 1
#define BP_CR2_HSI14DIS 2
#define MASK_CR2_HSI14TRIM 0x0000001f
#define BP_CR2_HSI14TRIM 3
#define MASK_CR2_HSI14CAL 0x000000ff
#define BP_CR2_HSI14CAL 8
#define BP_CR2_HSI48ON 16
#define BP_CR2_HSI48RDY 17
#define MASK_CR2_HSI48CAL 0x000000ff
#define BP_CR2_HSI48CAL 24


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
void stm_rcc_enable(uint32_t clock, uint32_t state);

#endif
