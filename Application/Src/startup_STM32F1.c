
#include <stdint.h> 
#include "startup_STM32F1.h"


unsigned int vectors[] __attribute__((section(".isr_vector")))= {
    STACK_START, 
    (unsigned int)Reset_Handler              , 
    (unsigned int)NMI_Handler                , 
    (unsigned int)HardFault_Handler          , 
    (unsigned int)MemManage_Handler          ,     
    (unsigned int)BusFault_Handler           , 
    (unsigned int)UsageFault_Handler         , 
    0,
    0,
    0,
    0,
    (unsigned int)SVC_Handler                ,    
    (unsigned int)DebugMon_Handler           , 
    0, 
    (unsigned int)PendSV_Handler             , 
    (unsigned int)SysTick_Handler            ,     
    (unsigned int)WWDG_IRQHandler            , 
    (unsigned int)PVD_Handler, 
    (unsigned int)TAMPER_IRQHandler          , 
    (unsigned int)RTC_IRQHandler             ,     
    (unsigned int)FLASH_IRQHandler           , 
    (unsigned int)RCC_IRQHandler             , 
    (unsigned int)EXTI0_IRQHandler           , 
    (unsigned int)EXTI1_IRQHandler           ,    
    (unsigned int)EXTI2_IRQHandler           , 
    (unsigned int)EXTI3_IRQHandler           , 
    (unsigned int)EXTI4_IRQHandler           ,
    (unsigned int)DMA1_Channel1_IRQHandler   ,
    (unsigned int)DMA1_Channel2_IRQHandler   ,
    (unsigned int)DMA1_Channel3_IRQHandler   ,
    (unsigned int)DMA1_Channel4_IRQHandler   ,
    (unsigned int)DMA1_Channel5_IRQHandler   ,
    (unsigned int)DMA1_Channel6_IRQHandler   ,
    (unsigned int)DMA1_Channel7_IRQHandler   ,    
    (unsigned int)ADC1_2_IRQHandler          ,
    (unsigned int)USB_HP_CAN1_TX_IRQHandler  ,    
    (unsigned int)USB_LP_CAN1_RX0_IRQHandler ,
    (unsigned int)CAN1_RX1_IRQHandler        ,    
    (unsigned int)CAN1_SCE_IRQHandler        ,
    (unsigned int)EXTI9_5_IRQHandler         ,    
    (unsigned int)TIM1_BRK_IRQHandler        ,
    (unsigned int)TIM1_UP_IRQHandler         ,    
    (unsigned int)TIM1_TRG_COM_IRQHandler    ,
    (unsigned int)TIM1_CC_IRQHandler         ,    
    (unsigned int)TIM2_IRQHandler            ,
    (unsigned int)TIM3_IRQHandler            ,    
    (unsigned int)TIM4_IRQHandler            ,    
    (unsigned int)I2C1_EV_IRQHandler         ,
    (unsigned int)I2C1_ER_IRQHandler         ,    
    (unsigned int)I2C2_EV_IRQHandler         ,
    (unsigned int)I2C2_ER_IRQHandler         ,    
    (unsigned int)SPI1_IRQHandler            ,
    (unsigned int)SPI2_IRQHandler            ,    
    (unsigned int)USART1_IRQHandler          ,
    (unsigned int)USART2_IRQHandler          ,        
    (unsigned int)USART3_IRQHandler          , 
    (unsigned int)EXTI15_10_IRQHandler       ,
    (unsigned int)RTC_Alarm_IRQHandler       ,   
    (unsigned int)USBWakeUp_IRQHandler
}; 

void Reset_Handler(void) {
    // copy .data section to RAM
    unsigned int size = (unsigned int)&_edata - (unsigned int)&_sdata; 
    unsigned char* pDst = (unsigned char*)&_sdata;           // SRAM
    unsigned char* pSrc = (unsigned char*) &_la_data;        // FLASH
    for(unsigned int i = 0; i < size; i++) {
        *pDst++ = *pSrc++; 
    }
    // init .bss section to zezo in RAM
    size = (unsigned int)&_ebss - (unsigned int)&_sbss; 
    pDst = (unsigned char*)&_sbss; 
    for(unsigned int i = 0; i < size; i++) {
        *pDst++ = 0; 
    }
    // call main() 
    main(); 

} 

void Default_Handler(void) {

    while(1);

}

