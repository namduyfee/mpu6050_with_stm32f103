
#include "I2C_Driver.h"


void config_I2C(void) 
{
    I2C1->CR1 |= (1<<15);   // reset the I2C
	I2C1->CR1 &= ~(1<<15);  // Normal operation

    // clock apb1
	I2C1->CR2 |= (36<<0);   // give data for i2c (data is clock of apb1), mpu don't calculate (a number) clock so we 
                            // must give data for it

	// check caculator in PDF
	I2C1->CCR |= 180<<0;    // fscl = 100khz         

	I2C1->TRISE = 37;       // config rise time register

    I2C1->CR2 |= 1<<8;      // enable error interrupt 

	I2C1->CR1 |= (1<<0);    // enable peripheral
	I2C1->CR1 |= (1<<10);   // Enable the ACK	    

}

void start_I2C(void)
{
    /*
     * mpu_6050 send 2 condition start, so unless enable ack here, ack is cleared after 1st
       and 2nd ack can clear -> error
     */
    I2C1->CR1 |= (1<<10);           // Enable the ACK
    I2C1->CR1 |= (1<<8);            // Generate START
    while (!(I2C1->SR1 & (1<<0)));  // Wait for SB bit to set
}

void stop_I2C (void)
{
    I2C1->CR1 |= (1<<9);  // Stop I2C
}

void send_address_I2C(uint8_t Address)
{   
    /*
     * because other device has other regulations, so to general i will write DR = Address
       and add or add + bit read/write is adjust by argument
     */

    I2C1->DR = Address;                     //  send the address
    while (!(I2C1->SR1 & (1<<1)));          // wait for ADDR bit to set
    uint16_t tem = I2C1->SR1 | I2C1->SR2;   // read SR1 and SR2 to clear the ADDR bit
}

void write_I2C (uint8_t data)
{
    
    while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set
    I2C1->DR = data;
    /*
     * make sure byte sended, after that continue next actives
       but it is little slow, because we can write DR when TXE is empty instead of must wait BTF
       wait condition can make stop condition 
     */
    while (!(I2C1->SR1 & (1<<2)));  // wait for BTF bit to set

}

void write_mutil_I2C(uint8_t *data, uint8_t size)
{

	while (size)
	{
		while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set 
		I2C1->DR = (uint32_t )(*data);  // send data
        data++; 
		size--;
	}
    /*
     * make sure last byte sended, after that continue next actives
       wait condition can make stop condition
     */
    while (!(I2C1->SR1 & (1<<2)));  // wait for BTF to set
} 

void read_I2C (uint8_t Address, uint8_t *buffer, uint8_t size)
{
    I2C1->CR1 |= (1<<10);                       // Enable the ACK
    uint8_t tem_size = size; 

    if(1 == size) {

		I2C1->DR = Address;                     //  send the address
		while (!(I2C1->SR1 & (1<<1)));          // wait for ADDR bit to set        
        I2C1->CR1 &= ~(1<<10);                  // clear the ACK bit 
        uint16_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit

        I2C1->CR1 |= (1<<9);                    // Stop I2C
        while (!(I2C1->SR1 & (1<<6)));          // wait for RxNE to set

        buffer[size-tem_size] = I2C1->DR;       // Read the data from the DATA REGISTER
        
    }
    else if(2 == size) {  

        I2C1->CR1 |= (1<<11);                   // Enable the POS   

		I2C1->DR = Address;                     //  send the address
		while (!(I2C1->SR1 & (1<<1)));          // wait for ADDR bit to set        
        uint16_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit 

        /*
         * Pos is set and ack is not set -> next byte(2nd byte) is transfer, nack is created 
           that mean current byte(1st byte) is sent ack (implicit).  
         */        
        I2C1->CR1 &= ~(1<<10);                   // clear the ACK bit 

        /*
         * ack or nack alway is made before RxNE or BTF is set so
           not wait BTF is set because in last byte nack is sent, when nack is sent or received 
           then BTF can not set 
         */
        while (!(I2C1->SR1 & (1<<6)));          // wait for first data into DR
        I2C1->CR1 |= (1<<9);                    // Stop I2C
        buffer[size-tem_size] = I2C1->DR;       // read first byte
        tem_size--;
        while (!(I2C1->SR1 & (1<<6)));          // wait for second data into DR
        buffer[size-tem_size] = I2C1->DR;       // read second byte 
        I2C1->CR1 &= ~(1<<11);                  // clear the POS bit

    }

    else {

		I2C1->DR = Address;                     //  send the address
		while (!(I2C1->SR1 & (1<<1)));          // wait for ADDR bit to set        
        uint16_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit

        while(tem_size > 3) {

            while (!(I2C1->SR1 & (1<<6)));      // wait for RxNE to set
            buffer[size-tem_size] = I2C1->DR;   // copy the data into the buffer
            tem_size--; 
        }

        while (!(I2C1->SR1 & (1<<6)));          // wait for RxNE to set, dataN-2 is received but not read
        while (!(I2C1->SR1 & (1<<2)));          // wait for BTF to set, dataN-1 is received 
        I2C1->CR1 &= ~(1<<10);                  // clear the ACK bit 
        buffer[size-tem_size] = I2C1->DR;       // read dataN-2
        tem_size--; 
        I2C1->CR1 |= (1<<9);                    // Stop I2C
        buffer[size-tem_size] = I2C1->DR;       // read dataN-1
        tem_size--; 
        while (!(I2C1->SR1 & (1<<6)));          // wait for RxNE to set
        buffer[size-tem_size] = I2C1->DR;

    }
}


