
#include "MPU_6050_Driver.h"

//#define SCALE_RANGE_GYROSCOPE	(0x00)      // +-250 o/s
//#define SCALE_RANGE_GYROSCOPE	(0x08)      // +-500 o/s
//#define SCALE_RANGE_GYROSCOPE	(0x10)      // +-1000 o/s
#define SCALE_RANGE_GYROSCOPE	(0x18)      // +-2000 o/s

#if SCALE_RANGE_GYROSCOPE == (0x18)
	#define DIV_GYRO 16.4f
#elif SCALE_RANGE_GYROSCOPE == (0x10)
	#define DIV_GYRO 32.8f
#elif SCALE_RANGE_GYROSCOPE == (0x08)
	#define DIV_GYRO 65.5f
#elif SCALE_RANGE_GYROSCOPE == (0x00)
	#define DIV_GYRO 131.0f
#endif


#define SCALE_RANGE_ACCELEROMETER	(0x00)  // +-2g
//#define SCALE_RANGE_ACCELEROMETER	(0x08)  // +-4g
//#define SCALE_RANGE_ACCELEROMETER	(0x10)  // +-8g  
//#define SCALE_RANGE_ACCELEROMETER	(0x18)  // +-16g

#if SCALE_RANGE_ACCELEROMETER == (0x18)
	#define DIV_ACCEL 2408.0f
#elif SCALE_RANGE_ACCELEROMETER == (0x10)
	#define DIV_ACCEL 4096.0f
#elif SCALE_RANGE_ACCELEROMETER == (0x08)
	#define DIV_ACCEL 8192.0f
#elif SCALE_RANGE_ACCELEROMETER == (0x00)
	#define DIV_ACCEL 16384.0f
#endif


DataMPU_Typedef Accel; 
DataMPU_Typedef Gyro; 

Angle_Typedef MPU; 


void config_MPU(void) 
{
	
	uint8_t checkConfigMPU;
	uint8_t dataConfigMPU;

	// check device ID WHO_AM_I

	mpu_read(MPU6050_ADDR,WHO_AM_I_REG, &checkConfigMPU, 1);

	if (checkConfigMPU == 104)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		dataConfigMPU = 0;
		mpu_write(MPU6050_ADDR, PWR_MGMT_1_REG, dataConfigMPU);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		dataConfigMPU = 0x07;
		mpu_write(MPU6050_ADDR, SMPLRT_DIV_REG, dataConfigMPU);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=SCALE_RANGE_ACCELEROMETER
		dataConfigMPU = SCALE_RANGE_ACCELEROMETER;
		mpu_write(MPU6050_ADDR, ACCEL_CONFIG_REG, dataConfigMPU);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=SCALE_RANGE_GYROSCOPE
		dataConfigMPU = SCALE_RANGE_GYROSCOPE;
		mpu_write(MPU6050_ADDR, GYRO_CONFIG_REG, dataConfigMPU);
    }
}

void mpu_write(uint8_t address, uint8_t reg, uint8_t data)
{
	start_I2C();
	send_address_I2C(address);
	write_I2C(reg);
	write_I2C(data);
	stop_I2C();
}

void mpu_read(uint8_t address, uint8_t reg, uint8_t *buffer, uint8_t size)
{
	start_I2C();
	send_address_I2C(address);
	write_I2C(reg);
	start_I2C();  // repeated start
	read_I2C(address+0x01, buffer, size);
//	stopI2c(); is created in function read i2c 
}

void mpu_read_accel_all(void)
{
	// g 
	
	uint8_t rxData[6];
	
	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	mpu_read(MPU6050_ADDR, ACCEL_XOUT_H_REG, rxData, 6);

	Accel.xRaw = (int16_t)(rxData[0] << 8 | rxData [1]);
	Accel.yRaw = (int16_t)(rxData[2] << 8 | rxData [3]);
	Accel.zRaw = (int16_t)(rxData[4] << 8 | rxData [5]);

// ACCEL +-2 => /16384
	
	Accel.xReal = (Accel.xRaw * 1.0f)/DIV_ACCEL;
	Accel.yReal = (Accel.yRaw * 1.0f)/DIV_ACCEL;
	Accel.zReal = (Accel.zRaw * 1.0f)/DIV_ACCEL;
}

void mpu_read_gyro_all(void) 
{
	// speed angle 
	
	uint8_t rxData[6];
	
	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	mpu_read(MPU6050_ADDR, GYRO_XOUT_H_REG, rxData, 6);

	Gyro.xRaw = (int16_t)(rxData[0] << 8 | rxData [1]);
	Gyro.yRaw = (int16_t)(rxData[2] << 8 | rxData [3]);
	Gyro.zRaw = (int16_t)(rxData[4] << 8 | rxData [5]);

	
	Gyro.xReal = (Gyro.xRaw * 1.0f)/DIV_GYRO;
	Gyro.yReal = (Gyro.yRaw * 1.0f)/DIV_GYRO;
	Gyro.zReal = (Gyro.zRaw * 1.0f)/DIV_GYRO;
}

void mpu_read_gyro_axis(char axis) 
{
	uint8_t rxData[2];

	if(axis == 'x'|| axis == 'X') {
		mpu_read(MPU6050_ADDR, GYRO_XOUT_H_REG, rxData, 2);
		Gyro.xRaw = (int16_t)(rxData[0] << 8 | rxData [1]);
		Gyro.xReal = (Gyro.xRaw * 1.0f)/DIV_GYRO;
	}

	else if(axis == 'y'|| axis == 'Y') {
		mpu_read(MPU6050_ADDR, GYRO_YOUT_H_REG, rxData, 2);
		Gyro.yRaw = (int16_t)(rxData[0] << 8 | rxData [1]);
		Gyro.yReal = (Gyro.yRaw * 1.0f)/DIV_GYRO;
	}

	else if(axis == 'z'|| axis == 'Z') {
		mpu_read(MPU6050_ADDR, GYRO_ZOUT_H_REG, rxData, 2);
		Gyro.zRaw = (int16_t)(rxData[0] << 8 | rxData [1]);
		Gyro.zReal = (Gyro.zRaw * 1.0f)/DIV_GYRO;
	}

}

void mpu_read_accel_axis(char axis) 
{
	uint8_t rxData[2];
	if(axis == 'x'|| axis == 'X') {
		mpu_read(MPU6050_ADDR, ACCEL_XOUT_H_REG, rxData, 2);
		Accel.xRaw = (int16_t)(rxData[0] << 8 | rxData [1]);
		Accel.xReal = (Accel.xRaw * 1.0f)/DIV_ACCEL;
	}

	else if(axis == 'y'|| axis == 'Y') {
		mpu_read(MPU6050_ADDR, ACCEL_YOUT_H_REG, rxData, 2);
		Accel.yRaw = (int16_t)(rxData[0] << 8 | rxData [1]);
		Accel.yReal = (Accel.yRaw * 1.0f)/DIV_ACCEL;
	}

	else if(axis == 'z'|| axis == 'Z') {
		mpu_read(MPU6050_ADDR, ACCEL_ZOUT_H_REG, rxData, 2);
		Accel.zRaw = (int16_t)(rxData[0] << 8 | rxData [1]);
		Accel.zReal = (Accel.zRaw * 1.0f)/DIV_ACCEL;
	}
}








