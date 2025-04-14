
#include "handler.h"

void HardFault_Handler(void) 

{

    while(1) {
        toggle_led(); 
    }
}

void EXTI0_IRQHandler(void)
{
	if( EXTI->PR & (1<<0) ) {
        
        if(enableSample == 0)
            enableSample = 1; 
        delayUs(10000); 
        
		EXTI->PR = 1<<0; 
	}
}

