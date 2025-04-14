
#include "EXTI_Driver.h"

void config_EXTI(void)
{
    // enable interrupt line 0
    EXTI->IMR |= 1; 

    // falling
    EXTI->FTSR |= 0X01;

}


