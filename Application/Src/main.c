
#include "main.h"

void main(void)
{
    config_RCC(); 
    config_GPIOC(); 
    config_TIM4(); 
    
    while(1) {
        toggle_led(); 
    }

}

