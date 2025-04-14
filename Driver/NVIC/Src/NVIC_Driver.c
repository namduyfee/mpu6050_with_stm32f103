
#include "NVIC_Driver.h"


void config_NVIC(void)
{
    __NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4); 

    __NVIC_SetPriority(EXTI0_IRQn, 1, 0); 

    __NVIC_EnableIRQ(EXTI0_IRQn); 


}

