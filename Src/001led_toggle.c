/*
 * 001led_toggle.c
 *
 *  Created on: Oct 23, 2022
 *      Author: Grétar Már Kjartansson
 */

#include "stm32f407xx.h"

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++); // Delay using for-loop
}

int main(void)
{

	// Create variable for API handle
	GPIO_Handle_t GpioLed, GPIOBtn; // Holds the base address of the GPIO port to which the pin belongs, can be = GPIOA, GPIOB ...


	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOD, ENABLE); // The clock is enabled for port D.
	GPIO_Init(&GpioLed); // Initialization of the register.

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12); //  Toggle the output pin
		delay();
	}

	return 0;
}
