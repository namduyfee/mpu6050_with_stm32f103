
#include "TIM_Driver.h"



void config_TIM4(void) 
{
    // config TIM4
    TIM4->ARR = 2000-1; 
    TIM4->PSC = 72-1; 
    TIM4->EGR |= 1; 
    TIM4->CR1 |= 1; 
}
    
void delayUs(uint32_t us) 
{
    
    while(us) {
    // SysTick->VAL = 0; 
        TIM4->CNT = 0; 
        while(TIM4->CNT == 0); 
        us--; 
    }
}

// Hàm toggle LED
void toggle_led(void) 
{
    GPIOC->ODR ^= (1 << 13);
    delayUs(100000); 

}

