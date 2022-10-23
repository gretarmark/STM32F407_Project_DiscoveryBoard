/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: Oct 16, 2022
 *      Author: Grétar Már Kjartansson
 */

#include "stm32f407xx_gpio_driver.h"


// Peripheral clock setup

// *************************************************************
// * @fn			- GPIO_PeriClockControl                    *    Function name
// * 						                                   *
// * @brief			- This function disables peripheral clock  *    Brief description
// * 				  for the given GPIO port				   *
// * 						                                   *
// * @param[in]		- Base address of the GPIO peripheral      *	Parameter description
// * @param[in]		- ENABLE or DISABLE macros	               *
// * @param[in]		- 		                                   *
// * 						                                   *
// * @return		- None	                                   *	Return type
// *														   *
// * @note			- None									   *	Any special note for using this API
// *************************************************************
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)		{ GPIOA_PCLK_EN(); }
		else if(pGPIOx == GPIOB){ GPIOB_PCLK_EN(); }
		else if(pGPIOx == GPIOC){ GPIOC_PCLK_EN(); }
		else if(pGPIOx == GPIOD){ GPIOD_PCLK_EN(); }
		else if(pGPIOx == GPIOE){ GPIOE_PCLK_EN(); }
		else if(pGPIOx == GPIOF){ GPIOF_PCLK_EN(); }
		else if(pGPIOx == GPIOG){ GPIOG_PCLK_EN(); }
		else if(pGPIOx == GPIOH){ GPIOH_PCLK_EN(); }
		else if(pGPIOx == GPIOI){ GPIOI_PCLK_EN(); }
	}
	else
	{
		if(pGPIOx == GPIOA)		{ GPIOA_PCLK_DI(); }
		else if(pGPIOx == GPIOB){ GPIOB_PCLK_DI(); }
		else if(pGPIOx == GPIOC){ GPIOC_PCLK_DI(); }
		else if(pGPIOx == GPIOD){ GPIOD_PCLK_DI(); }
		else if(pGPIOx == GPIOE){ GPIOE_PCLK_DI(); }
		else if(pGPIOx == GPIOF){ GPIOF_PCLK_DI(); }
		else if(pGPIOx == GPIOG){ GPIOG_PCLK_DI(); }
		else if(pGPIOx == GPIOH){ GPIOH_PCLK_DI(); }
		else if(pGPIOx == GPIOI){ GPIOI_PCLK_DI(); }
	}
}

// Init and De-init

// *************************************************************
// * @fn			- GPIO_init			                       *    Function name
// * 						                                   *
// * @brief			- This function disables peripheral clock  *    Brief description
// * 				  for the given GPIO port				   *
// * 						                                   *
// * @param[in]		- Base address of the GPIO peripheral      *	Parameter description
// * @param[in]		- 							               *
// * @param[in]		- 		                                   *
// * 						                                   *
// * @return		- None	                                   *	Return type
// *														   *
// * @note			- None									   *	Any special note for using this API
// *************************************************************
void GPIO_init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp;	//Temporary register

	// 1. Configure the mode of gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		// The non-interrupt mode
		// Each pin takes 2 bit fields
		temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // Need to clear the bitfield before, just in case if it's not cleared.
		pGPIOHandle->pGPIOx->MODER |= temp; // Setting - Use bitwise or her, not only equal sign. We don't want to
											// affect other bits of this register.
	}
	else
	{
		// This part will be coded later (interrupt mode)
	}

	temp = 0;
	// 2. Configure the speed
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // Need to clear the bitfield before, just in case if it's not cleared.
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	// 3. Configure the pupd settings (Pull-Up, Pull-Down)
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // Need to clear the bitfield before, just in case if it's not cleared.
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	// 4. Configure the optype (output type)
	// Each pin takes 1 bit field, so multiplying by 2 is not required
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); // Need to clear the bitfield before, just in case if it's not cleared.
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;

	// 5. Configure the alt (alternate) functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		// Configure the alt function registers
		uint32_t temp1, temp2;

		// The divition is integer, so it results in whole numbers
		// The mod of 8 will give the rest of the divition.
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;


		pGPIOHandle->pGPIOx->AFR[temp1] &= ~( 0xF << ( 4*temp2 ) ); //Clearing
		pGPIOHandle->pGPIOx->AFR[temp1] |= ( pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ( 4*temp2 ) );

	}

}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) // Put reset bit to 1 will reset the whole port that is inputted
{
	if(pGPIOx == GPIOA)		{ GPIOA_REG_RESET(); }
	else if(pGPIOx == GPIOB){ GPIOB_REG_RESET(); }
	else if(pGPIOx == GPIOC){ GPIOC_REG_RESET(); }
	else if(pGPIOx == GPIOD){ GPIOD_REG_RESET(); }
	else if(pGPIOx == GPIOE){ GPIOE_REG_RESET(); }
	else if(pGPIOx == GPIOF){ GPIOF_REG_RESET(); }
	else if(pGPIOx == GPIOG){ GPIOG_REG_RESET(); }
	else if(pGPIOx == GPIOH){ GPIOH_REG_RESET(); }
	else if(pGPIOx == GPIOI){ GPIOI_REG_RESET(); }
}

// Data read and write

// *************************************************************
// * @fn			- GPIO_ReadFromInputPin	                   *    Function name
// * 						                                   *
// * @brief			- This function reads values from  		   *    Brief description
// * 				  input pin								   *
// * 						                                   *
// * @param[in]		- GPIOx Peripheral					       *	Parameter description
// * @param[in]		- Number of the pin 		               *
// * @param[in]		- 		                                   *
// * 						                                   *
// * @return		- uint8_t                                  *	Return type
// *														   *
// * @note			- None									   *	Any special note for using this API
// *************************************************************
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;

	value = (uint8_t)( (pGPIOx->IDR >> PinNumber) & 0x00000001 ); // Right shift in the amount of pinnumbers.
																  // We only care about the least-significant bit
																  // That's why 0x00000001 is chosen.
																  // IDR: Input Data Register
	return value;
}


// *************************************************************
// * @fn			- GPIO_ReadFromInputPort                   *    Function name
// * 						                                   *
// * @brief			- This function reads values from  		   *    Brief description
// * 				  input port							   *
// * 						                                   *
// * @param[in]		- GPIOx Peripheral					       *	Parameter description
// *  				  (Base Address of the GPIO Port)		   *
// * @param[in]		- 							               *
// * @param[in]		- 		                                   *
// * 						                                   *
// * @return		- uint16_t                                 *	Return type
// *														   *
// * @note			- None									   *	Any special note for using this API
// *************************************************************
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx) // 16 pins, so we need uint16
{
	uint16_t value;

	value = (uint16_t)pGPIOx->IDR; // IDR: Input Data Register

	return value;
}

// *************************************************************
// * @fn			- GPIO_WriteToOutputPin                    *    Function name
// * 						                                   *
// * @brief			- Writes "Value" to the "PinNumber" pin    *    Brief description
// * 				  							   			   *
// * 						                                   *
// * @param[in]		- GPIOx Peripheral 						   *	Parameter description
// *                  (Base Address of the GPIO Port)		   *
// * @param[in]		- The number of the pin to be used         *
// * @param[in]		- Value to be written to "PinNumber" pin   *
// * 				  The value can be 1 or 0.	               *
// *														   *
// * @return		- none                                     *	Return type
// *														   *
// * @note			- None									   *	Any special note for using this API
// *************************************************************
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value) // Value = 0 or 1, set/reset
{
	if(Value == GPIO_PIN_SET)
	{
		//Write 1 to the output data register at the corresponding pinnumber
		pGPIOx->ODR |= (1 << PinNumber); // Output data register
	}
	else
	{
		// Else write 0
		pGPIOx->ODR &= ~(1 << PinNumber); // Clear position of the pin
	}
}

// *************************************************************
// * @fn			- GPIO_WriteToOutputPort                   *    Function name
// * 						                                   *
// * @brief			- 									       *    Brief description
// * 				  							   			   *
// * 						                                   *
// * @param[in]		- GPIOx Peripheral 						   *	Parameter description
// *                  (Base Address of the GPIO Port)		   *
// * @param[in]		- Value of the pin used at the moment      *
// * @param[in]		-    									   *
// *														   *
// * @return		- None                                     *	Return type
// *														   *
// * @note			- None									   *	Any special note for using this API
// *************************************************************
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value; // We simply need to write the value to the Output Data Register
}


// *************************************************************
// * @fn			- GPIO_ToggleOutputPin                     *    Function name
// * 						                                   *
// * @brief			- 									       *    Brief description
// * 				  							   			   *
// * 						                                   *
// * @param[in]		- GPIOx Peripheral 						   *	Parameter description
// *                  (Base Address of the GPIO Port)		   *
// * @param[in]		- The number of the pin being used         *
// * @param[in]		-    									   *
// *														   *
// * @return		- None                                     *	Return type
// *														   *
// * @note			- None									   *	Any special note for using this API
// *************************************************************
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	//pGPIOx->ODR = pGPIOx->ODR ^ (1 << PinNumber); // ^ is a bitwise or opperation
	pGPIOx->ODR ^= (1 << PinNumber); // ^ is a bitwise X-OR opperation
}

// IRQ Configuration and ISR handling
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)	//Used to configure the IRQ number of the GPIO pin, like enable, set priority and more...
{

}

void GPIO_IRQHandling(uint8_t PinNumber)
{

}
