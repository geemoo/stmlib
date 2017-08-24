#ifndef __STM32F_GPIO_H__
#define __STM32F_GPIO_H__

/*
 * define structs
 */

/// device struct for GPIO hardware
struct stm_gpio_dev {
	/// 0x00 : mode register
	uint32_t mode;

	/// 0x04 : output type register
	uint16_t type;

	/// 0x06 : reserved
	uint16_t reserved0;

	/// 0x08 : output speed register
	uint32_t speed;

	/// 0x0c : pull-up/pull-down register
	uint32_t pupd;

	/// 0x10 : input data register
	uint16_t in;

	/// 0x12 : reserved
	uint16_t reserved1;

	/// 0x14 : output data register
	uint16_t out;

	/// 0x16 : reserved
	uint16_t reserved2;

	/// 0x18 : bit set/reset register
	uint32_t bsr;

	/// 0x1c : configuration lock register
	uint32_t lock;

	/// 0x20 : alternate function low register
	uint32_t afl;

	/// 0x24 : alternate function high register
	uint32_t afh;

	/// 0x28 : bit reset register
	uint16_t br;

	/// 0x2a : reserved
	uint16_t reserved3;
};


/*
 * define hardware aliases
 */

/// GPIO addresses
#define GPIO_BASE 0x48000000
#define GPIOA ((struct stm_gpio_dev *) (GPIO_BASE + 0x0000))
#define GPIOB ((struct stm_gpio_dev *) (GPIO_BASE + 0x0400))
#define GPIOC ((struct stm_gpio_dev *) (GPIO_BASE + 0x0800))
#define GPIOD ((struct stm_gpio_dev *) (GPIO_BASE + 0x0C00))
#define GPIOE ((struct stm_gpio_dev *) (GPIO_BASE + 0x1000))
#define GPIOF ((struct stm_gpio_dev *) (GPIO_BASE + 0x1400))


/*
 * define interface functions
 */

void stm_gpio_setup(struct stm_gpio_dev *dev, uint32_t pins, uint32_t mode, uint32_t pull, uint32_t speed); 
void stm_gpio_af(struct stm_gpio_dev *dev, uint32_t af); 

#endif
