
#ifndef __AFIO_DRIVER__

#define __AFIO_DRIVER__

#include "main.h"


#define AFIO ((AFIO_TypeDef*)(AFIO_BASE))

typedef struct
{
  __IO uint32_t EVCR;
  __IO uint32_t MAPR;
  __IO uint32_t EXTICR[4];
  uint32_t RESERVED0;
  __IO uint32_t MAPR2;  
} AFIO_TypeDef;


void config_AFIO(void);

#endif
