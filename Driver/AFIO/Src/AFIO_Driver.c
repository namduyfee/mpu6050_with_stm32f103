
#include "AFIO_Driver.h"

void config_AFIO(void) 
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	// I2C remap 
	AFIO->MAPR |= 1<<1; 

    // PA0 for line 0
    AFIO->EXTICR[0] &= 0xFFFFFFF0; 

}

