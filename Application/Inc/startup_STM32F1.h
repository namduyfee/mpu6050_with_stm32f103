
#ifndef __STARTUP__
#define __STARTUP__

#define SRAM_START  0x20000000U
#define SRAM_SIZE (20U * 1024U)     // 20K byte 
#define SRAM_END ( (SRAM_START) + (SRAM_SIZE) )
#define STACK_START SRAM_END

extern unsigned int _etext; 
extern unsigned int _sdata; 
extern unsigned int _edata; 
extern unsigned int _sbss; 
extern unsigned int _ebss; 
extern unsigned int _la_data; 

void main(void); 

void Default_Handler(void); 

void Reset_Handler(void); 
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler"))); 
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler"))); 
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler"))); 
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler"))); 
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler"))); 
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler"))); 
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler"))); 
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler"))); 
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler"))); 
void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void PVD_Handler(void) __attribute__((weak, alias("Default_Handler"))); 
void TAMPER_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void RTC_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void RCC_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void EXTI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void EXTI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void EXTI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void EXTI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void EXTI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void DMA1_Channel1_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void DMA1_Channel2_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void DMA1_Channel3_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void DMA1_Channel4_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void DMA1_Channel5_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void DMA1_Channel6_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void DMA1_Channel7_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void ADC1_2_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void USB_HP_CAN1_TX_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void USB_LP_CAN1_RX0_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void CAN1_RX1_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void CAN1_SCE_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void EXTI9_5_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void TIM1_BRK_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void TIM1_UP_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void TIM1_TRG_COM_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void TIM4_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void I2C1_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void I2C1_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void I2C2_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void I2C2_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void USART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void EXTI15_10_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void RTC_Alarm_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 
void USBWakeUp_IRQHandler(void) __attribute__((weak, alias("Default_Handler"))); 

#endif

