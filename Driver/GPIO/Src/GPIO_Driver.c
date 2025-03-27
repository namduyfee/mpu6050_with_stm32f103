
#include "GPIO_Driver.h"


void config_GPIOC(void) 
{

	GPIOC->CRH = 0; 
	GPIOC->CRH |= (0x3<<20); 

}


