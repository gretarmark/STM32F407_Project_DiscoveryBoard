/*
 * stm32f407xx.h
 *
 *  Created on: Sep 8, 2022
 *      Author: Grétar Már Kjartansson
 */

#include <stdint.h>

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#define __vo volatile

// Base addresses of Flash and SRAM memories

#define FLASH_STM32 0x4002 3C00 //- 0x4002 3FFF
#define SRAM_STM32

// By default, these numbers are considered as signed numbers (signed integers)
// but addresses can't be signed. We have to cast them to unsigned.
// #define FLASH_BASEADDR (uint32_t) 0x08000000 is same as 0x08000000U
// Main memory is FLASH memory and System memory is ROM memory (page 71 or in ch. 3)
// Note that the numbers below are HEX numbers.
#define FLASH_BASEADDR 					0x08000000U 	// p. 71 eða table 5 - Main Memory
#define SRAM1_BASEADDR 					0x20000000U 	// p. 71 - Main internal SRAM1 (112 KB)
#define SRAM2_BASEADDR 					0x2001C000U		// p. 71 - Auxiliary internal SRAM2 (16 KB)
#define ROM_BASEADDR					0x1FFF0000U		// p. 71 - System Memory (30 kbytes)
#define SRAM 							SRAM1_BASEADDR	// SRAM1 is SRAM (base SRAM)

// Calculate base address C macros for MCU
// SRAM2 base address - SRAM1 is 112 KB, so after 112 KB the SRAM2 appears.
// Convert from KB to Bytes: 112 * 1024 = 114688 bytes -> convert to HEX:
// Use programmer calculator to get: HEX = 1 C000. This is why
// SRAM2_BASEADDR = 0x2001C000U

// Full memory map of STM32F4 starts at ? to ? (0xFFFFFFFF ?). The peripheral base starts
// from 0x40000000(PERIPH_BASE). The first peripheral that appears at the peripheral base is
// Timer 2, 0x4000 0000 - 0x4000 03FF (TIM2). After that we have to go to TIM2 in PDF to find out
// what register it is. Go to register map at ch. 18.4.21. The register is called TIM2_CR2


// AHBx and APBx BUS Peripheral base addresses
#define PERIPH_BASEADDR					0x40000000U 	// Peripheral Base - TIM2 starts at this address, p.67 Table 1
#define APB1PERIPH_BASEADDR				PERIPH_BASEADDR // TIM2 is connected to APB1 peripheral BUS
#define APB2PERIPH_BASEADDR				0x40010000U		// TIM1 is connected to APB2 peripheral BUS
#define AHB1PERIPH_BASEADDR				0x40020000U		// GPIOA register
#define AHB2PERIPH_BASEADDR				0x50000000U		// USB OTG FS connected to AHB2 BUS

// Base addresses of peripherals which are hanging on AHB1 bus

// Calculate GPIOA_BASEADDR: We know it is hanging on
									  //(AHB1PERIPH_BASEADDR + OFFSET)
#define GPIOA_BASEADDR 					(AHB1PERIPH_BASEADDR + 0x0000)	// The offset for GPIOA is 0000 because it's
																		// the first peripheral that appears on the AHB1 BUS
#define GPIOB_BASEADDR 					(AHB1PERIPH_BASEADDR + 0x0400)  // The offset is 0x0400 for GPIOB
#define GPIOC_BASEADDR 					(AHB1PERIPH_BASEADDR + 0x0800)  //
#define GPIOD_BASEADDR 					(AHB1PERIPH_BASEADDR + 0x0C00)  //
#define GPIOE_BASEADDR 					(AHB1PERIPH_BASEADDR + 0x1000)	//
#define GPIOF_BASEADDR 					(AHB1PERIPH_BASEADDR + 0x1400)	//
#define GPIOG_BASEADDR 					(AHB1PERIPH_BASEADDR + 0x1800)	//
#define GPIOH_BASEADDR 					(AHB1PERIPH_BASEADDR + 0x1C00)	//
#define GPIOI_BASEADDR 					(AHB1PERIPH_BASEADDR + 0x2000)	//

#define RCC_BASEADDR					(AHB1PERIPH_BASEADDR + 0x3800) // RCC is connected to AHB1 bus. 0x4002 3800 - 0x4002 3BFF

// Base addresses of peripherals which are hanging on APB1 bus
									  //(APB1PERIPH_BASEADDR + OFFSET)
#define I2C1_BASEADDR					(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR					(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR					(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR					(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR					(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR					(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR					(APB1PERIPH_BASEADDR + 0x4800)

#define UART4_BASEADDR					(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR					(APB1PERIPH_BASEADDR + 0x5000)

// Base addresses of peripherals which are hanging on APB2 bus

#define EXTI_BASE						(APB2PERIPH_BASEADDR + 0x3C00)
#define SPI1_BASE						(APB2PERIPH_BASEADDR + 0x3000)
#define SYSCFG_BASE						(APB2PERIPH_BASEADDR + 0x3800)
#define USART1_BASE						(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASE						(APB2PERIPH_BASEADDR + 0x1400)

// Address offsets for registers of SPI1
// Control Register 1: 0x00 - ch. 28.5.1
// Control Register 2: 0x04 - ch. 28.5.2
// Status Register: 0x08
// Data Register: 0x0C
// CRC Polynomial Register: 0x10
// RX CRC Register: 0x14
// TX CRC Register: 0x18
// Configuration Register: 0x1C
// Prescaler Register: 0x20

typedef struct {
	__vo uint32_t MODER;	//GPIO port mode register                 - Address Offset: 0x00
	__vo uint32_t OTYPER;	//GPIO port output type register          - Address Offset: 0x04
	__vo uint32_t OSPEEDR;	//GPIO port output speed register         - Address Offset: 0x08
	__vo uint32_t PUPDR;	//GPIO port pull-up/pull-down register    - Address Offset: 0x0C
	__vo uint32_t IDR;		//GPIO port input data register           - Address Offset: 0x10
	__vo uint32_t ODR;		//GPIO port output data register          - Address Offset: 0x14
	__vo uint32_t BSRR;		//GPIO port bit set/reset register        - Address Offset: 0x18
	__vo uint32_t LCKR;		//GPIO port configuration lock register   - Address Offset: 0x1C
	__vo uint32_t AFR[2]; //AFR[0]:AFRL, GPIO alternate function low register  - Address Offset: 0x20
					 	  //AFR[1]:AFRH, GPIO alternate function high register - Address Offset: 0x24
}GPIO_RegDef_t;

typedef struct {
	__vo uint32_t CR;			// RCC clock control register 		- Address Offset: 0x00
	__vo uint32_t PLLCFGR;		// RCC PLL configuration register 	- Address Offset: 0x04
	__vo uint32_t CFGR;			// RCC clock configuration register - Address Offset: 0x08
	__vo uint32_t CIR;			// RCC clock interrupt register - Address Offset: 0x0C
	__vo uint32_t AHB1RSTR;		// RCC AHB1 peripheral reset register - Address Offset: 0x10
	__vo uint32_t AHB2RSTR;		// RCC AHB2 peripheral reset register - Address Offset: 0x14
	__vo uint32_t AHB3RSTR;		// RCC AHB3 peripheral reset register - Address Offset: 0x18
	uint32_t RESERVED0;			// RESERVED - Address Offset: 0x1C
	__vo uint32_t APB1RSTR;		// RCC APB1 peripheral reset register - Address Offset: 0x20
	__vo uint32_t APB2RSTR;		// RCC APB2 peripheral reset register - Address Offset: 0x24
	uint32_t RESERVED1[2];		// RESERVED - Address Offset: 0x28 and 0x2C
	__vo uint32_t AHB1ENR;		// RCC AHB1 peripheral clock enable register - Address Offset: 0x30
	__vo uint32_t AHB2ENR;		// RCC AHB2 peripheral clock enable register - Address Offset: 0x34
	__vo uint32_t AHB3ENR;		// RCC AHB3 peripheral clock enable register - Address Offset: 0x38
	uint32_t RESERVED2;			// RESERVED - Address Offset: 0x3C
	__vo uint32_t APB1ENR;		// RCC APB1 peripheral clock enable register - Address Offset: 0x40
	__vo uint32_t APB2ENR;		// RCC APB2 peripheral clock enable register - Address Offset: 0x44
	uint32_t RESERVED3[2];		// RESERVED - Address Offset: 0x48 and 0x4C
	__vo uint32_t AHB1LPENR;	// RCC AHB1 peripheral clock enable in low power mode register - Address Offset: 0x50
	__vo uint32_t AHB2LPENR;	// RCC AHB2 peripheral clock enable in low power mode register - Address Offset: 0x54
	__vo uint32_t AHB3LPENR;	// RCC AHB3 peripheral clock enable in low power mode register - Address Offset: 0x58
	uint32_t RESERVED4;			// RESERVED - Address Offset: 0x5C
	__vo uint32_t APB1LPENR;	// RCC APB1 peripheral clock enable in low power mode register - Address Offset: 0x60
	__vo uint32_t APB2LPENR;	// RCC APB2 peripheral clock enabled in low power mode register - Address Offset: 0x64
	uint32_t RESERVED5[2];		// RESERVED - Address Offset: 0x68 & 0x6C
	__vo uint32_t BDCR;			// RCC Backup domain control register - Address Offset: 0x70
	__vo uint32_t CSR;			// RCC clock control & status register - Address Offset: 0x74
	uint32_t RESERVED6[2];		// RESERVED - Address Offset: 0x78 & 0x7C
	__vo uint32_t SSCGR;		// RCC spread spectrum clock generation register - Address Offset: 0x80
	__vo uint32_t PLLI2SCFGR;	// RCC PLLI2S configuration register - Address Offset: 0x84
	__vo uint32_t PLLSAICFGR;	// to do - Address Offset: 0x88
	__vo uint32_t DCKCFGR;		// to do - Address Offset: 0x8C
	__vo uint32_t CKGATENR;		// to do - Address Offset: 0x90
	__vo uint32_t DCKCFGR2;		// to do - Address Offset: 0x94
}RCC_RegDef_t;

// Peripheral definition (Peripheral base addresses typecasted to xxx_RegDef_t)
#define GPIOA 		((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB 		((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC 		((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD 		((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE 		((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF 		((GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG 		((GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH 		((GPIO_RegDef_t*) GPIOH_BASEADDR)
#define GPIOI 		((GPIO_RegDef_t*) GPIOI_BASEADDR)

#define RCC			((RCC_RegDef_t*)RCC_BASEADDR)

// Clock Enable Macros for GPIOx peripherals
# define GPIOA_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 0) ) // Peripheral Clock Enabled
# define GPIOB_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 1) ) // Peripheral Clock Enabled (see ch. 7.3.10)
# define GPIOC_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 1) )
# define GPIOD_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 1) )
# define GPIOE_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 1) )
# define GPIOF_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 1) )
# define GPIOG_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 1) )
# define GPIOH_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 1) )
# define GPIOI_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 1) )
// Clock Enable Macros for I2Cx peripherals
# define I2C1_PCLK_EN()			( RCC->APB1ENR |= ( 1 << 21) ) //I2C1 Enable is bit 21 (see ch. 7.3.13)
// Clock Enable Macros for SPIx peripherals
# define SPI1_PCLK_EN()			( RCC->APB2ENR |= ( 1 << 12) )
// Clock Enable Macros for USARTx peripherals
# define USART1_PCLK_EN()			( RCC->APB2ENR |= ( 1 << 4) )
// Clock Enable Macros for SYSCFG peripherals
# define SYSCFG_PCLK_EN()			( RCC->APB2ENR |= ( 1 << 14) )

// Clock Disable Macros for GPIOx peripherals
// Remember we use bitwise or to set a bit. We use bitwise and to reset a bit.
// Use negation symbol, ~ (NOT). Now we have a way to clear a bit.
# define GPIOA_PCLK_DI()			( RCC->AHB1ENR &= ~( 1 << 0) )

// Macros to reset GPIOx peripherals
// How to include two statements in 1 single macro? The trick is to use do-while loop
// This is a technique in C to execute multiple C statements using single C macro
#define GPIOA_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 0) );  (RCC->AHB1RSTR &= ~(1 << 0)); }while(0) //no need for semicolon here, it will be done later
#define GPIOB_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 1) );  (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()			do{ ( RCC->AHB1RSTR |= ( 1 << 2) );  (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)

// Some generic macros

#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET


#endif /* INC_STM32F407XX_H_ */
