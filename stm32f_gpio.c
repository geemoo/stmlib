#include <stdint.h>
#include "stm32f0xx.h"

/**
 * setup pins on a GPIO port
 *
 * @param dev - the GPIO device to setup
 * @param pins - a bitmask of pins to change
 * @param mode - the pin mode to change to
 * @param type - the pin type to use, pushpull or opendrain
 * @param pull - what kind of pullup/down should be set
 * @param speed - what speed of pin
 */
void stm_gpio_setup(struct stm_gpio_dev *dev, uint32_t pins, uint32_t mode, uint32_t type, uint32_t pull, uint32_t speed)
{
	int index;
	int index2;

	// pins can be a bit mask of pin numbers to change.. loop across it
	index = 0;
	index2 = 0;
	while (pins) {
		// set mode
		dev->MODER = (dev->MODER & ~(0x3 << index2)) | (mode << index2);

		// set output type
		if (type)
			dev->TYPER |= (1 << index);
		else
			dev->TYPER &= ~(1 << index);

		// set speed
		dev->OSPEEDR = (dev->OSPEEDR & ~(0x3 << index2)) | (speed << index2);

		// set pull
		dev->PUPDR = (dev->PUPDR & ~(0x3 << index2)) | (pull << index2);

		// inc indexes
		index += 1;
		index2 += 2;

		// shift pins
		pins = pins >> 1;
	}
}


/**
 * setup the alternate function of a pin
 *
 * @param dev - the GPIO device to setup
 * @param af - the alternate function number to select
 */
void stm_gpio_af(struct stm_gpio_dev *dev, uint32_t af)
{
}

