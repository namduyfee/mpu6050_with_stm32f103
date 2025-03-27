
#ifndef __RCC_HSE__

#define __RCC_HSE__

#include "main.h"


#define  RCC_CR_HSEON       ((uint32_t)0x00010000)
#define  RCC_CR_HSERDY      ((uint32_t)0x00020000)

#if !defined  (HSE_STARTUP_TIMEOUT) 
  #define HSE_STARTUP_TIMEOUT    ((uint16_t)0x0500)   /*!< Time out for HSE start up */
#endif /* HSE_STARTUP_TIMEOUT */

#endif

