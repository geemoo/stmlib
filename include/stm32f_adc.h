#ifndef __STM32F_ADC_H__
#define __STM32F_ADC_H__

#include <stdint.h>


/*
 * define constants
 */

/// ISR bits
#define BP_ADC_AWD 7
#define BP_ADC_OVR 4
#define BP_ADC_EOSEQ 3
#define BP_ADC_EOC 2
#define BP_ADC_EOSMP 1
#define BP_ADC_ADRDY 0

/// CR bits
#define BP_ADC_ADCAL 31
#define BP_ADC_ADSTART 2
#define BP_ADC_ADDIS 1
#define BP_ADC_ADEN 0


/*
 * declare structs
 */

struct stm_adc_dev {
	volatile uint32_t ISR;
	volatile uint32_t IER;
	volatile uint32_t CR;
	volatile uint32_t CFGR1;
	volatile uint32_t CFGR2;
	volatile uint32_t SMPR;
	uint32_t reserved1[2];
	volatile uint32_t TR;
	uint32_t reserved2;
	volatile uint32_t CHSELR;
	uint32_t reserved[5];
	volatile uint32_t DR;
};


/*
 * define hardware aliases
 */
#define ADC ((struct stm_adc_dev *) (0x40012400))


/* 
 * function defines
 */

void stm_adc_setup(void);
void stm_adc_cal(void);
void stm_adc_enable(int);
void stm_adc_chansel(uint8_t);

#endif

