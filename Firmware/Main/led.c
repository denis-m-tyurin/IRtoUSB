#include "led.h"
#include "stm32f0xx.h"

void leds_init()
{
		// Enable clock for I/O port A
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
		// Set output mode for PA1, PA2 and PA3
		GPIOA->MODER |= GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0;
	
		// Set PA1 to push-pull mode
		GPIOA->OTYPER &= ~GPIO_OTYPER_OT_1;
		// Set PA2 to push-pull mode
		GPIOA->OTYPER &= ~GPIO_OTYPER_OT_2;
		// Set PA3 to push-pull mode
		GPIOA->OTYPER &= ~GPIO_OTYPER_OT_3;
	
		// Disable pull-up pull-down
		GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR1;
		GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR2;
		GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR3;
	
		// Default output level is 0, which is LED ON, set it to 1 to switch LED OFF
		GPIOA->BSRR |= GPIO_BSRR_BS_1;
		GPIOA->BSRR |= GPIO_BSRR_BS_2;
		GPIOA->BSRR |= GPIO_BSRR_BS_3;
		
		return;
}

void leds_red_on()
{
	GPIOA->BRR |= GPIO_BSRR_BS_1;
	
	return;
}

void leds_red_off()
{
	GPIOA->BSRR |= GPIO_BSRR_BS_1;
	
	return;
}