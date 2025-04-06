
#ifndef __GPIO_DRIVER__
#define __GPIO_DRIVER__

#include "main.h"

#define GPIOB ((GPIO_TypeDef*)(GPIOB_BASE))
#define GPIOC ((GPIO_TypeDef*)(GPIOC_BASE))
#define AFIO ((AFIO_TypeDef*)(AFIO_BASE))

typedef struct
{
  __IO uint32_t EVCR;
  __IO uint32_t MAPR;
  __IO uint32_t EXTICR[4];
  uint32_t RESERVED0;
  __IO uint32_t MAPR2;  
} AFIO_TypeDef;

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

void config_AFIO(void);

void config_GPIOC(void); 
void config_GPIOB(void); 

#endif
