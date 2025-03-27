
#ifndef __GPIO_DRIVER__
#define __GPIO_DRIVER__

#include "main.h"


#define GPIOC ((GPIO_TypeDef*)(GPIOC_BASE))


typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;

} GPIO_TypeDef;



void config_GPIOC(void); 


#endif
