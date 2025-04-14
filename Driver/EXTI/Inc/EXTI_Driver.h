
#ifndef __EXTI_DRIVER__
#define __EXTI_DRIVER__

#include "main.h"

#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)

typedef struct
{
  __IO uint32_t IMR;
  __IO uint32_t EMR;
  __IO uint32_t RTSR;
  __IO uint32_t FTSR;
  __IO uint32_t SWIER;
  __IO uint32_t PR;
} EXTI_TypeDef;


void config_EXTI(void); 

#endif

