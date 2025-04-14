
#include "GPIO_Driver.h"
void config_GPIOA(void) 
{
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL = 0; 
	
	GPIOA->CRL |= 0x08;        // PA0 input pull up/pull down
	GPIOA->ODR |= 1;           // PA0 input pull up

}

void config_GPIOC(void) 
{

	GPIOC->CRH = 0; 
	GPIOC->CRH |= (0x3<<20); 
	OFF_LED_SAMPLE_KALMAN; 


}

void config_GPIOB(void)
{
	RCC->APB2ENR |= 1<<3;
	// CRH = 0
	GPIOB->CRH &= 0; 
	// PB8, PB9 output alternate open drain 
	GPIOB->CRH |= 0xFF;

}

