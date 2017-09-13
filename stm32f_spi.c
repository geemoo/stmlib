#include <stdint.h>
#include <string.h>
#include "stm32f0xx.h"


/*
 * define constants
 */

/// CR1
#define BP_SPI_CR1_SSM 9
#define BP_SPI_CR1_SSI 8
#define BP_SPI_CR1_SPE 6
#define MASK_SPI_CR1_BR 0x00000007
#define BP_SPI_CR1_BR 3
#define BP_SPI_CR1_MSTR 2
#define BP_SPI_CR1_CPOL 1
#define BP_SPI_CR1_CPHA 0

/// CR2
#define MASK_SPI_CR2_DS 0x0000000f
#define BP_SPI_CR2_DS 8

/// SR
#define BP_SPI_SR_BSY 7
#define BP_SPI_SR_TXE 1
#define BP_SPI_SR_RXNE 0

/// slave cache mask CR1
#define MASK_SLAVE_CR1 ((MASK_SPI_CR1_BR << BP_SPI_CR1_BR) | (1 << BP_SPI_CR1_CPOL) | (1 << BP_SPI_CR1_CPHA))


/*
 * declare private functions
 */
static uint32_t stm_spi_div2br(uint16_t div);


/*
 * functions
 */

/**
 * setup an SPI port
 *
 * @param dev - the SPI device to setup
 * @param dev_ss - the GPIO port the slave select pins are in
 * @param mask_ss - a bitmask of pins that are used for slave selects
 * @param dev_sclk - the GPIO port the sclk pin is on
 * @param bp_sclk - the bit position of the sclk pin
 * @param dev_mosi - the GPIO port the mosi pin is on
 * @param bp_mosi - the bit position of the mosi pin
 * @param dev_miso - the GPIO port the miso pin is on
 * @param bp_miso - the bit position of the miso pin
 */
void stm_spi_setup(volatile struct stm_spi_dev *dev, volatile struct stm_gpio_dev *dev_ss, uint32_t mask_ss, volatile struct stm_gpio_dev *dev_sclk, uint32_t bp_sclk, volatile struct stm_gpio_dev *dev_mosi, uint32_t bp_mosi, volatile struct stm_gpio_dev *dev_miso, uint32_t bp_miso)
{
	// setup the slave selects
	stm_gpio_setup(dev_ss, mask_ss, GPIO_OUTPUT, GPIO_PUSHPULL, GPIO_PULLUP, GPIO_HIGHSPEED);

	// bring slaves high (for now, we only support active low SS)
	dev_ss->BSRR = mask_ss;

	// setup the sclk
	if (dev_sclk) {
		stm_gpio_af(dev_sclk, (1 << bp_sclk), GPIO_AF_SPI);
		stm_gpio_setup(dev_sclk, (1 << bp_sclk), GPIO_AF, GPIO_PUSHPULL, GPIO_PULLDOWN, GPIO_HIGHSPEED);
	}

	// setup the mosi
	if (dev_mosi) {
		stm_gpio_af(dev_mosi, (1 << bp_mosi), GPIO_AF_SPI);
		stm_gpio_setup(dev_mosi, (1 << bp_mosi), GPIO_AF, GPIO_PUSHPULL, GPIO_PULLDOWN, GPIO_HIGHSPEED);
	}

	// setup the miso
	if (dev_miso) {
		stm_gpio_af(dev_miso, (1 << bp_miso), GPIO_AF_SPI);
		stm_gpio_setup(dev_miso, (1 << bp_miso), GPIO_AF, GPIO_PUSHPULL, GPIO_PULLDOWN, GPIO_HIGHSPEED);
	}

	// master mode
	dev->CR1 |= (1 << BP_SPI_CR1_MSTR);

	// 8 bit transfers
	dev->CR2 = (dev->CR2 & ~(MASK_SPI_CR2_DS << BP_SPI_CR2_DS)) | (7 << BP_SPI_CR2_DS); // 8 bit transfers

	// flush RX fifo
	while (dev->SR & (1 << BP_SPI_SR_RXNE))
		dev->DR;
}


/**
 * setup a new spi slave
 *
 * @param slave - a pointer to the slave struct we're going to setup
 * @param dev - the SPI device to setup
 * @param cfg - the spi configuration
 * @param ssdev - the GPIO port the slave select pins are in
 * @param sspin - the bit position of the slave select pin
 */
void stm_spi_newslave(struct stm_spi_slave *slave, volatile struct stm_spi_dev *dev, struct stm_spi_cfg *cfg, volatile struct stm_gpio_dev *ssdev, uint32_t sspin)
{
	// store params in slave object
	slave->spidev = dev;
	memcpy(&slave->spicfg, cfg, sizeof(struct stm_spi_cfg));
	slave->ssdev = ssdev;
	slave->sspin = sspin;

	// compile baud rate
	slave->cr1 = (stm_spi_div2br(cfg->clkdiv) << BP_SPI_CR1_BR);

	// compile clock polarity and phase
	if ((cfg->clkpol == SPI_CLKPOL_LOW) && (cfg->clkedge == SPI_CLKEDGE_RISING)) {
		slave->cr1 |= (0 << BP_SPI_CR1_CPOL) | (0 << BP_SPI_CR1_CPHA);
	} else if ((cfg->clkpol == SPI_CLKPOL_LOW) && (cfg->clkedge == SPI_CLKEDGE_FALLING)) {
		slave->cr1 |= (0 << BP_SPI_CR1_CPOL) | (1 << BP_SPI_CR1_CPHA);
	} else if ((cfg->clkpol == SPI_CLKPOL_HIGH) && (cfg->clkedge == SPI_CLKEDGE_RISING)) {
		slave->cr1 |= (1 << BP_SPI_CR1_CPOL) | (1 << BP_SPI_CR1_CPHA);
	} else if ((cfg->clkpol == SPI_CLKPOL_HIGH) && (cfg->clkedge == SPI_CLKEDGE_FALLING)) {
		slave->cr1 |= (1 << BP_SPI_CR1_CPOL) | (0 << BP_SPI_CR1_CPHA);
	}
}	


/**
 * convert a divider to a baud rate bit value
 *
 * @param div - the clk divider value
 * @return - the baud rate bits to set
 */
static uint32_t stm_spi_div2br(uint16_t div)
{
	int i;

	// first we bounds check
	if (div <= 2)
		return 0x0;
	if (div >= 256)
		return 0x7;

	/*
	 * we can only handle powers of 2, so just count how many shifts until 
	 * 0 and compute from that bit value.  since we end looping at 0, and min is 2, 
	 * we have to shift twice to get an accurate count
	 */
	div = div >> 2;

	// count from here
	i = 0;
	while (div) {
		div = div >> 1;
		i += 1;
	}

	return i;
}


/**
 * send a word through the SPI
 *
 * @param cfg - the SPI configuration to use
 * @param data - the bits to send
 */
void stm_spi_send(struct stm_spi_slave *slave, uint32_t data)
{
	volatile struct stm_spi_dev *spidev = slave->spidev;
	int wc;
	int pos;
	uint8_t bits;

	// write our cached configuration, and enable the spi device
	spidev->CR1 = (spidev->CR1 & ~MASK_SLAVE_CR1) | slave->cr1;
	spidev->CR1 = spidev->CR1 | (1 << BP_SPI_CR1_MSTR) | (1 << BP_SPI_CR1_SSM) | (1 << BP_SPI_CR1_SSI);
	spidev->CR2 = (spidev->CR2 & ~(0xf << 8)) | (7 << 8);
	spidev->CR2 |= (1 << 12);
	spidev->CR1 = spidev->CR1 | (1 << BP_SPI_CR1_SPE);

	// activate slave (for now, we only support active low)
	slave->ssdev->BSRR = (1 << (slave->sspin + 16));

	// write data into fifo
	wc = slave->spicfg.bitlen >> 3;
	while (wc) {

		// write data, 8 bits at a time, starting at MSB
		pos = 8 * (wc - 1);
		bits = data >> pos;

		// we have to cast the DR register to an 8 bit pointer, if we want to only write 8 bits
		*((uint8_t *) &spidev->DR) = bits;

		// dec word count
		wc -= 1;
	}

	// wait until done
	while (spidev->SR & (1 << BP_SPI_SR_BSY));

	// release slave
	slave->ssdev->BSRR = (1 << slave->sspin);
}


