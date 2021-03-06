/**
  ******************************************************************************
  * @file    system_stm32f0xx.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    05-December-2014
  * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer System Source File.
  *          This file contains the system clock configuration for STM32F0xx devices,
  *          and is generated by the clock configuration tool  
  *          STM32F0xx_Clock_Configuration_V1.0.0.xls
  *
  * 1.  This file provides two functions and one global variable to be called from 
  *     user application:
  *      - SystemInit(): Setups the system clock (System clock source, PLL Multiplier
  *                      and Divider factors, AHB/APBx prescalers and Flash settings),
  *                      depending on the configuration made in the clock xls tool.
  *                      This function is called at startup just after reset and 
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32f0xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick 
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  * 2. After each device reset the HSI (8 MHz Range) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_stm32f0xx.s" file, to
  *    configure the system clock before to branch to main program.
  *
  * 3. If the system clock source selected by user fails to startup, the SystemInit()
  *    function will do nothing and HSI still used as system clock source. User can 
  *    add some code to deal with this issue inside the SetSysClock() function.
  *
  * 4. The default value of HSE crystal is set to 8MHz, refer to "HSE_VALUE" define
  *    in "stm32f0xx.h" file. When HSE is used as system clock source, directly or
  *    through PLL, and you are using different crystal you have to adapt the HSE
  *    value to your own configuration.
  *
  * 5. This file configures the system clock as follows:
  *=============================================================================
  *                         System Clock Configuration
  *=============================================================================
  *        System Clock source          | PLL(HSE)
  *-----------------------------------------------------------------------------
  *        SYSCLK                       | 48000000 Hz
  *-----------------------------------------------------------------------------
  *        HCLK                         | 48000000 Hz
  *-----------------------------------------------------------------------------
  *        AHB Prescaler                | 1
  *-----------------------------------------------------------------------------
  *        APB1 Prescaler               | 1
  *-----------------------------------------------------------------------------
  *        APB2 Prescaler               | 1
  *-----------------------------------------------------------------------------
  *        HSE Frequency                | 8000000 Hz
  *-----------------------------------------------------------------------------
  *        PLL MUL                      | 6
  *-----------------------------------------------------------------------------
  *        VDD                          | 3.3 V
  *-----------------------------------------------------------------------------
  *        Flash Latency                | 1 WS
  *-----------------------------------------------------------------------------
  *=============================================================================
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "stm32f0xx.h"

/*
 * declare globals
 */
uint32_t SystemCoreClock = 48000000;


/*
 * declare private functions
 */

static void __sysclk_setup(void);


/**
 * Setup the microcontroller system.  Initialize the Embedded Flash Interface,
 * the PLL and update the SystemCoreClock variable.
 */
void __system_init(void)
{
	uint32_t bits;

	// set HSION bit
	RCC->CR |= (1 << BP_CR_HSION);

#ifdef STM32F051
	// reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits
	bits = (MASK_CFGR_SW << BP_CFGR_SW) \
	       | (MASK_CFGR_HPRE << BP_CFGR_PPRE) \
	       | (1 << BP_CFGR_ADCPRE)  \
	       | (1 << BP_CFGR_MCO);
	RCC->CFGR &= ~bits;
#else
	// reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE, MCOSEL[2:0], MCOPRE[2:0] and PLLNODIV bits
	RCC->CFGR &= (uint32_t)0x08FFB80C;
#endif
  
	// Reset HSEON, CSSON and PLLON bits
	RCC->CR &= ~(1 << BP_CR_HSEON);
	RCC->CR &= ~(1 << BP_CR_CSSON);
	RCC->CR &= ~(1 << BP_CR_PLLON);

	// reset HSEBYP bit
	RCC->CR &= (1 << BP_CR_HSEBYP);

	// reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits
	RCC->CFGR &= ~(MASK_CFGR_PLLSRC << BP_CFGR_PLLSRC);
	RCC->CFGR &= ~(1 << BP_CFGR_PLLXTPRE);
	RCC->CFGR &= ~(MASK_CFGR_PLLMUL << BP_CFGR_PLLMUL);

	// reset PREDIV1[3:0] bits
	RCC->CFGR2 &= ~(MASK_CFGR2_PREDIV << BP_CFGR2_PREDIV);

	// reset USARTSW[1:0], I2CSW, CECSW and ADCSW bits
	RCC->CFGR3 &= ~(MASK_CFGR3_USART1SW << BP_CFGR3_USART1SW);
	RCC->CFGR3 &= ~(1 << BP_CFGR3_I2C1SW);
	RCC->CFGR3 &= ~(1 << BP_CFGR3_CECSW);
	RCC->CFGR3 &= ~(1 << BP_CFGR3_ADC1SW);

	// reset HSI14 bit
	RCC->CR2 &= ~(1 << BP_CR2_HSI14ON);

	// disable all interrupts
	RCC->CIR = 0x00000000;

  	// do sysclk setup
	__sysclk_setup();
}


static void __sysclk_setup(void)
{
	uint32_t bits;
	uint32_t timeout;

	// enable HSE
	RCC->CR |= (1 << BP_CR_HSEON);
 
	// wait until HSE is ready, or timeout is reached
	timeout = 0x5000;
	while (timeout && !(RCC->CR & (1 << BP_CR_HSERDY)));
		timeout--;

	// check if HSE is ready now (we could have timedout instead)
	if (RCC->CR & (1 << BP_CR_HSERDY)) {

		// enable Prefetch Buffer and set Flash Latency to 1
    		bits = FLASH->ACR & ~(MASK_ACR_LATENCY << BP_ACR_LATENCY);
    		FLASH->ACR = bits | (1 << BP_ACR_PRFTBE) | (1 << BP_ACR_LATENCY);
 
		// set hclk to sysclk
		RCC->CFGR = (RCC->CFGR & ~(MASK_CFGR_HPRE << BP_CFGR_HPRE)) | (0 << BP_CFGR_HPRE);
      
		// set pclk to hclk
		RCC->CFGR = (RCC->CFGR & ~(MASK_CFGR_PPRE << BP_CFGR_PPRE)) | (0 << BP_CFGR_PPRE);

		// configure PLL to HSE * 6 ( 48 MHz )
		RCC->CFGR = (RCC->CFGR & ~(MASK_CFGR_PLLSRC << BP_CFGR_PLLSRC)) | (2 << BP_CFGR_PLLSRC);
		RCC->CFGR = (RCC->CFGR & ~(1 << BP_CFGR_PLLXTPRE));
		RCC->CFGR = (RCC->CFGR & ~(MASK_CFGR_PLLMUL << BP_CFGR_PLLMUL)) | ((6 - 2) << BP_CFGR_PLLMUL);
            
		// enable the PLL
		RCC->CR |= (1 << BP_CR_PLLON);

		// wait until the PLL is ready
		while(!(RCC->CR & (1 << BP_CR_PLLRDY)));

		// select the PLL as the system clock source
		RCC->CFGR = (RCC->CFGR & ~(MASK_CFGR_SW << BP_CFGR_SW)) | (2 << BP_CFGR_SW);

		// wait until the PLL is selected in status
		while (((RCC->CFGR >> BP_CFGR_SWS) & MASK_CFGR_SWS) != 2);

	// HSE timed out
	} else {
		// no clock means no hope.. just kinda sit here
		for (;;);
	}
}


