
#include "config.h"

void config_STM32F1(void) 
{
    config_RCC(); 
    
    config_GPIOC();
    config_GPIOB(); 
    config_AFIO(); 
    
    config_TIM4(); 
    
    config_I2C(); 

    config_MPU();  

    kalman_filter_init_accel();

}

