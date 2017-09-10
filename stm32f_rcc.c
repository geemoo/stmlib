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
	uint32_t *reg;

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

	// determine which register to toggle
	if (clock & (1 << 30))
		reg = &RCC->AHBENR;
	else if (clock & (2 << 30))
		reg = &RCC->APB2ENR;
	else if (clock & (3 << 30))
		reg = &RCC->APB1ENR;

	// determine upper or lower bits (we'll just reuse clock)
	if (clock & (1 << 29))
		clock = (clock & 0x0000ffff) << 16;
	else
		clock = (clock & 0x0000ffff) << 0;

	// toggle bits according to state
	if (state)
		*reg = *reg | clock;
	else
		*reg = *reg & ~clock;
}

