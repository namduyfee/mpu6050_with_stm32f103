
#include "main.h"


void main(void)
{

    config_STM32F1();

    while(1) {

        mpu_read_accel_all(); 

		Accel.xKalman = Kalman_update(&kf_x_accel, Accel.xReal);
		Accel.yKalman = Kalman_update(&kf_y_accel, Accel.yReal);
		Accel.zKalman = Kalman_update(&kf_z_accel, Accel.zReal);
        
		MPU.roll  = (atan(Accel.yKalman / sqrt(pow(Accel.xKalman, 2) + pow(Accel.zKalman, 2))) * 180 * 1.0f / PI); 
		MPU.pitch = (atan(-Accel.xKalman / sqrt(pow(Accel.yKalman, 2) + pow(Accel.zKalman, 2))) * 180 * 1.0f / PI);
        
        delayUs(1000); 
    }

}

