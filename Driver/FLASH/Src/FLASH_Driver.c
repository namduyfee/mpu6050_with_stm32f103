
#include "FLASH_Driver.h"


void config_FLASH(void) 
{
	// 48Mhz < SYSCLK <= 72 Mhz
	FLASH->ACR |= 1<<2; 
	
	/*
	// 24 Mhz < SYSCLK <= 48 Mhz 
	FLASH->ACR |= 1<<1; 
	*/
	
	/*
	// 0 < SYSCLK <= 24 Mhz 
	FLASH->ACR &= (~1); 
	FLASH->ACR &= (~(1<<1)); 
	*/
}


void Flash_Lock(void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}


void Flash_Unlock(void)
{
	FLASH->KEYR = 0x45670123; 
	FLASH->KEYR = 0xCDEF89AB; 
}

void Flash_Erase(uint32_t addr)
{
	Flash_Unlock();
	while((FLASH->SR & FLASH_SR_BSY));
	FLASH->CR |= FLASH_CR_PER; 			//Page Erase Set
	FLASH->AR = addr; 					//Page Address
	FLASH->CR |= FLASH_CR_STRT; 		//Start Page Erase
	while((FLASH->SR & FLASH_SR_BSY));
	FLASH->CR &= ~FLASH_SR_BSY;
	FLASH->CR &= ~FLASH_CR_PER; 		//Page Erase Clear
}

int Flash_Write_16bits(uint32_t addr, uint16_t* dataIn, uint32_t length)
{
	if(addr % 2U != 0U)
		return FLASH_ERROR;
	Flash_Unlock();
	FLASH->CR |= FLASH_CR_PG;				/*!< Programming */

	for(uint32_t i=0; i < length; i++) {
    	while((FLASH->SR & FLASH_SR_BSY));
    	*(__IO uint16_t*)(addr + i*2) = (uint16_t)dataIn[i];
  	}

	while((FLASH->SR&FLASH_SR_BSY));
	FLASH->CR &= ~FLASH_CR_PG; 
	Flash_Lock();
	return FLASH_NOT_ERROR;
}

int Flash_Read_16bits(uint32_t addr, uint16_t* dataOut, uint32_t length)
{
	if(addr % 2U != 0U)
		return FLASH_ERROR; 
	for(uint32_t i=0; i < length; i++)
		*(uint16_t*)(dataOut+i) = *(__IO uint16_t*)(addr + i*2);
	return FLASH_NOT_ERROR; 
}

int Flash_Write_8bits(uint32_t addr, uint8_t* dataIn, uint32_t length)
{
	if(addr % 2U != 0)
		return FLASH_ERROR; 

	Flash_Unlock();
  	FLASH->CR |= FLASH_CR_PG;

  	for(uint32_t i = 0; i < length; i++) {

    	while((FLASH->SR & FLASH_SR_BSY));
    	*(__IO uint16_t*)(addr + i*2) = (uint16_t)dataIn[i];;
  	}	
	while((FLASH->SR&FLASH_SR_BSY));
  	FLASH->CR &= ~FLASH_CR_PG;
  	Flash_Lock(); 
}

int Flash_Read_8bits(uint32_t addr, uint8_t* dataOut, uint32_t length)
{
	if(dataOut == 0U || length == 0U)
		return FLASH_ERROR; 
	for(uint32_t i = 0; i < length; i++) {
		*(uint8_t*)(dataOut + i) = *(uint8_t*)(addr + i*2); 
	}
	return FLASH_NOT_ERROR; 
}

int Flash_Write_32bits(uint32_t addr, uint32_t* dataIn, uint32_t length)
{
	if(addr % 2U != 0U)
		return FLASH_ERROR;
	
	Flash_Unlock();
	FLASH->CR |= FLASH_CR_PG;				/*!< Programming */

	for(uint32_t i=0; i < length; i++) {

    	while((FLASH->SR & FLASH_SR_BSY));
    	*(__IO uint16_t*)(addr + i*4) = (uint16_t)(dataIn[i] & 0x0000FFFF);
		while((FLASH->SR & FLASH_SR_BSY));
		*(__IO uint16_t*)(addr + (i*4 + 2)) = (uint16_t)( (dataIn[i]>>16) & 0x0000FFFF);
  	}

	while((FLASH->SR&FLASH_SR_BSY));
	FLASH->CR &= ~FLASH_CR_PG; 
	Flash_Lock();
	return FLASH_NOT_ERROR;
}

int Flash_Read_32bits(uint32_t addr, uint32_t* dataOut, uint32_t length)
{
	if(addr % 2U != 0U)
		return FLASH_ERROR; 

	uint32_t bitsLow, bitsHigh; 

	for(uint32_t i=0; i < length; i++) {
		bitsLow = *(__IO uint16_t*)(addr + i*4);
		bitsHigh = *(__IO uint16_t*)(addr + i*4 + 2);
		*(uint32_t*)(dataOut+i) = (uint32_t)(bitsHigh<<16) | (uint32_t)bitsLow; 
	}
	return FLASH_NOT_ERROR; 
}



