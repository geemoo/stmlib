#ifndef __STM32F_RCC_H__
#define __STM32F_RCC_H__

#define RCC_GPIOA 0x00020000
#define RCC_GPIOB 0x00040000
#define RCC_GPIOC 0x00080000
#define RCC_GPIOD 0x00100000
#define RCC_GPIOE 0x00200000
#define RCC_GPIOF 0x00400000

/* 
 * function defines
 */
uint32_t stm_rcc_enable(uint32_t clock, uint32_t state);

#endif
