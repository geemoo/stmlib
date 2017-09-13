#ifndef __STM32F_GPIO_H__
#define __STM32F_GPIO_H__

/*
 * define constants
 */

/// mode
#define GPIO_INPUT 0x00
#define GPIO_OUTPUT 0x01
#define GPIO_AF 0x02
#define GPIO_ANALOG 0x03

/// output types
#define GPIO_PUSHPULL 0x00
#define GPIO_OPENDRAIN 0x01

/// pullup/pulldown values
#define GPIO_NOPULL 0x00
#define GPIO_PULLUP 0x01
#define GPIO_PULLDOWN 0x02

/// output speed
#define GPIO_LOWSPEED 0x0
#define GPIO_MEDSPEED 0x1
#define GPIO_HIGHSPEED 0x3

/// alternate function numbers
#define GPIO_AF_SPI 0


/*
 * define structs
 */

/// device struct for GPIO hardware
struct stm_gpio_dev {
	/// 0x00 : mode register
	uint32_t MODER;

	/// 0x04 : output type register
	uint32_t TYPER;

	/// 0x08 : output speed register
	uint32_t OSPEEDR;

	/// 0x0c : pull-up/pull-down register
	uint32_t PUPDR;

	/// 0x10 : input data register
	uint16_t IDR;

	/// 0x12 : reserved
	uint16_t RESERVED0;

	/// 0x14 : output data register
	uint16_t ODR;

	/// 0x16 : reserved
	uint16_t RESERVED1;

	/// 0x18 : bit set/reset register
	uint32_t BSRR;

	/// 0x1c : configuration lock register
	uint32_t LCKR;

	/// 0x20 : alternate function low register
	uint32_t AFRL;

	/// 0x24 : alternate function high register
	uint32_t AFRH;

	/// 0x28 : bit reset register
	uint16_t BRR;

	/// 0x2a : reserved
	uint16_t RESERVED2;
};


/*
 * define hardware aliases
 */

/// GPIO addresses
#define GPIO_BASE 0x48000000
#define GPIOA ((volatile struct stm_gpio_dev *) (GPIO_BASE + 0x0000))
#define GPIOB ((volatile struct stm_gpio_dev *) (GPIO_BASE + 0x0400))
#define GPIOC ((volatile struct stm_gpio_dev *) (GPIO_BASE + 0x0800))
#define GPIOD ((volatile struct stm_gpio_dev *) (GPIO_BASE + 0x0C00))
#define GPIOE ((volatile struct stm_gpio_dev *) (GPIO_BASE + 0x1000))
#define GPIOF ((volatile struct stm_gpio_dev *) (GPIO_BASE + 0x1400))


/*
 * define interface functions
 */

void stm_gpio_setup(volatile struct stm_gpio_dev *dev, uint32_t pins, uint32_t mode, uint32_t type, uint32_t pull, uint32_t speed); 
void stm_gpio_af(volatile struct stm_gpio_dev *dev, uint32_t pins, uint32_t af);

#endif
