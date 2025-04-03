
#ifndef __I2C_DRIVER__

#define __I2C_DRIVER__

#include "main.h"


#define I2C1 ((I2C_TypeDef *) I2C1_BASE)
#define I2C2 ((I2C_TypeDef *) I2C2_BASE)


typedef struct
{
  __IO uint16_t CR1;
  uint16_t  RESERVED0;
  __IO uint16_t CR2;
  uint16_t  RESERVED1;
  __IO uint16_t OAR1;
  uint16_t  RESERVED2;
  __IO uint16_t OAR2;
  uint16_t  RESERVED3;
  __IO uint16_t DR;
  uint16_t  RESERVED4;
  __IO uint16_t SR1;
  uint16_t  RESERVED5;
  __IO uint16_t SR2;
  uint16_t  RESERVED6;
  __IO uint16_t CCR;
  uint16_t  RESERVED7;
  __IO uint16_t TRISE;
  uint16_t  RESERVED8;
} I2C_TypeDef; 

void config_I2C(void); 
void start_I2C(void); 
void write_I2C (uint8_t data);  
void send_address_I2C(uint8_t address); 
void stop_I2C (void); 
void read_I2C (uint8_t address, uint8_t *buffer, uint8_t size); 
void write_mutil_I2C(uint8_t *data, uint8_t size); 


#endif

