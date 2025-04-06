
#ifndef __MPU_6050_DRIVER__

#define __MPU_6050_DRIVER__

#include "main.h"


#define MPU6050_ADDR 0xD0

#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19

#define ACCEL_CONFIG_REG 0x1C
#define GYRO_CONFIG_REG 0x1B 

#define ACCEL_XOUT_H_REG 0x3B
#define ACCEL_XOUT_L_REG 0x3C

#define ACCEL_YOUT_H_REG 0x3D
#define ACCEL_YOUT_L_REG 0x3E

#define ACCEL_ZOUT_H_REG 0x3F
#define ACCEL_ZOUT_L_REG 0x40

#define GYRO_XOUT_H_REG 0x43
#define GYRO_XOUT_L_REG 0x44

#define GYRO_YOUT_H_REG 0x45
#define GYRO_YOUT_L_REG 0x46

#define GYRO_ZOUT_H_REG 0x47
#define GYRO_ZOUT_L_REG 0x48

#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define INT_STATUS 0x3A

#define SAVE_X_AXIS_ADDR	((uint32_t)0x0801FC00) // page 127
#define SAVE_Y_AXIS_ADDR	((uint32_t)(SAVE_X_AXIS_ADDR + 4)) // page 127
#define SAVE_Z_AXIS_ADDR	((uint32_t)(SAVE_Y_AXIS_ADDR + 4)) // page 127


typedef struct {
    int16_t xRaw; 
	int16_t yRaw; 
	int16_t zRaw; 
    float xReal; 
	float yReal; 
	float zReal; 
    float xKalman; 
	float yKalman; 
	float zKalman; 		
} DataMPU_Typedef; 

typedef struct {
	int16_t pitch; 
	int16_t roll; 
} Angle_Typedef;


extern DataMPU_Typedef Accel; 
extern DataMPU_Typedef Gyro; 
extern Angle_Typedef MPU; 


void config_MPU(void); 
void mpu_write (uint8_t address, uint8_t reg, uint8_t data); 
void mpu_read(uint8_t address, uint8_t reg, uint8_t *buffer, uint8_t size); 

void mpu_read_accel_all(void); 
void mpu_read_gyro_all(void); 

void mpu_read_gyro_axis(char axis); 
void mpu_read_accel_axis(char axis); 



#endif
