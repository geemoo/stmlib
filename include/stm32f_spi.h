#ifndef __STM32F_SPI_H__
#define __STM32F_SPI_H__

#include <stdint.h>


/*
 * define constants
 */

/// SPI clock polarity
#define SPI_CLKPOL_LOW 0
#define SPI_CLKPOL_HIGH 1

/// SPI data loads on edge
#define SPI_CLKEDGE_RISING 1
#define SPI_CLKEDGE_FALLING 2

/*
 * declare structs
 */

struct stm_spi_dev {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
};


/// SPI configuration
struct stm_spi_cfg {
	/// bits per word
	uint32_t bitlen;

	/// clock divisor
	uint32_t clkdiv;

	/// clock polarity
	uint32_t clkpol;

	/// do we set data on the rising or falling edge?
	uint32_t clkedge;
};

/// SPI slave object
struct stm_spi_slave {

	/// which device does this slave use
	volatile struct stm_spi_dev *spidev;

	/// which port is the slave select on
	volatile struct stm_gpio_dev *ssdev;

	/// spi configuration
	struct stm_spi_cfg spicfg;

	/// which GPIO pin number is the slave select
	uint32_t sspin;

	/// compiled configuration
	uint32_t cr1;
};


/*
 * define hardware aliases
 */
#define SPI1 ((volatile struct stm_spi_dev *) (0x40013000))
#define SPI2 ((volatile struct stm_spi_dev *) (0x40003800))


/* 
 * function defines
 */
void stm_spi_setup(volatile struct stm_spi_dev *dev, volatile struct stm_gpio_dev *dev_ss, uint32_t mask_ss, volatile struct stm_gpio_dev *dev_sclk, uint32_t bp_sclk, volatile struct stm_gpio_dev *dev_mosi, uint32_t bp_mosi, volatile struct stm_gpio_dev *dev_miso, uint32_t bp_miso);
void stm_spi_newslave(struct stm_spi_slave *slave, volatile struct stm_spi_dev *dev, struct stm_spi_cfg *cfg, volatile struct stm_gpio_dev *ssdev, uint32_t sspin);
void stm_spi_send(struct stm_spi_slave *slave, uint32_t data);

#endif
