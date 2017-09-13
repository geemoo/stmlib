#include <stdint.h>
#include "stm32f0xx.h"

/**
 * setup pins on a GPIO port
 *
 * @param clock - which clock we're going to enable/disable (See RCC_* in stm32_rcc.h)
 * @param state - 1 to enable, 0 to disable
 */
void stm_rcc_enable(uint32_t clock, uint32_t state)
{
	uint32_t val;
	uint32_t reg;

	/*
	 * The clock variable is a constant which comprises a bit field containing the following bits:
	 * - [31:30] - an identifier indicating the register we want to toggle, 
	 *   	- 1 indicates RCC_AHBENR
	 *   	- 2 indicates RCC_APB2ENR
	 *   	- 3 indicates RCC_APB1ENR
	 * - [29] - indicates whether we are toggling the lower 16 bits, or the upper 16 bits
	 *   	- 1 indicates upper 16 bits
	 *   	- 0 indicates lower 16 bits
	 * - [28:16] - ignored
	 * - [15:0] - the bit positions we are toggling
	 */

	// determine value to mask in.. is it in the upper or lower bits
	if (clock & (1 << 29))
		val = (clock & 0x0000ffff) << 16;
	else
		val = (clock & 0x0000ffff) << 0;

	// determine which register to toggle
	reg = (clock >> 30) & 0x00000003;

	// now adjust the register, depending on state
	if (state) {
		if (reg == 1)
			RCC->AHBENR |= val;

		else if (reg == 2)
			RCC->APB2ENR |= val;

		else if (reg == 3)
			RCC->APB1ENR |= val;
	
	} else {
		if (reg == 1)
			RCC->AHBENR &= ~val;

		else if (reg == 2)
			RCC->APB2ENR &= ~val;

		else if (reg == 3)
			RCC->APB1ENR &= ~val;
	}
}

