/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Oct 16, 2022
 *      Author: Grétar Már Kjartansson
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t GPIO_PinNumber;			//Possible values from @GPIO_PIN_NUMBERS
	uint8_t GPIO_PinMode;		  	//Possible values from @GPIO_PIN_MODES
	uint8_t GPIO_PinSpeed;			//Possible values from @GPIO_PIN_SPEED
	uint8_t GPIO_PinPuPdControl;	//Possible values from @GPIO_PIN_PUPD
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

// Handle structure for GPIO pin
typedef struct
{
	// Pointer to hold the base address of the GPIO peripheral
	GPIO_RegDef_t *pGPIOx; // Holds the base address of the GPIO port to which the pin belongs, can be = GPIOA, GPIOB ...
	GPIO_PinConfig_t GPIO_PinConfig; // Holds GPIO pin configuration settings

}GPIO_Handle_t;

// GPIO pin numbers
// @GPIO_PIN_NUMBERS
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15

// *******************************
// *   Possible GPIO pin modes   *
// *******************************

// GPIO port mode register modes (ch. 8.4.1)
// @GPIO_PIN_MODES
#define GPIO_MODE_IN		0	// Input (reset state)
#define GPIO_MODE_OUT		1	// General purpose output mode
#define GPIO_MODE_ALTFN		2	// Alternate function mode
#define GPIO_MODE_ANALOG	3	// Analog mode
#define GPIO_MODE_IT_FT		4	// Interrupt mode. IT: Input Trigger, FT: Falling Edge Trigger
#define GPIO_MODE_IT_RT		5	// Interrupt mode. RT: Rising Edge Trigger
#define GPIO_MODE_IT_RFT	6	// Interrupt mode. Rising-Falling Edge Trigger

// GPIO port output type register modes (ch. 8.4.2)
#define GPIO_MODE_PP		0	// Output push-pull (reset state)
#define GPIO_MODE_OD		1	// Output open-drain

// GPIO port output speed register modes (ch. 8.4.3)
// @GPIO_PIN_SPEED
#define GPIO_MODE_LOW		0	// Low Speed
#define GPIO_MODE_MEDIUM	1	// Medium Speed
#define GPIO_MODE_FAST		2	// High Speed
#define GPIO_MODE_HIGH		3	// Very High Speed

// GPIO port pull-up/pull-down register modes (ch. 8.4.4)
// @GPIO_PIN_PUPD
#define GPIO_NO_PUPD		0	// No pull-up, pull-down
#define GPIO_PIN_PU			1	// Pull-up
#define GPIO_PIN_PD			2	// Pull-down

//


// **********************************************************************
// *               APIs supported by this driver                        *
// * For more information about the APIs check the function definitions *
// **********************************************************************

// Peripheral clock setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

// Init and De-init
void GPIO_init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx); // Put reset bit to 1 will reset the whole port that is inputted

// Data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx); // 16 pins, so we need uint16
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value); // Value = 0 or 1, set/reset
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

// IRQ Configuration and ISR handling
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);	//Used to configure the IRQ number of the GPIO pin, like enable, set priority and more...
void GPIO_IRQHandling(uint8_t PinNumber);



#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
