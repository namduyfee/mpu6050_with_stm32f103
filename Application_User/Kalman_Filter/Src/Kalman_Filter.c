
#include "Kalman_Filter.h"

#define SAMPLE_SIZE 250

uint8_t enableSample = 0; 
uint32_t tem_kalman[6];

KalmanFilter kf_x_accel;
KalmanFilter kf_y_accel;
KalmanFilter kf_z_accel;

void Kalman_init(KalmanFilter* kf, float q, float r, float initial_value) 
{
    kf->q = q;
    kf->r = r;
    kf->x = initial_value;
    kf->p = 1.0f;
    kf->k = 0.0f;
}

float Kalman_update(KalmanFilter* kf, float measurement) 
{
    kf->p += kf->q;
    kf->k = kf->p / (kf->p + kf->r);
    kf->x += kf->k * (measurement - kf->x);
    kf->p *= (1.0f - kf->k);
    return kf->x;
}

float compute_mean(float* data, int n) 
{
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

float compute_variance(float* data, int n, float mean) 
{
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        float diff = data[i] - mean;
        sum += diff * diff;
    }
    return sum / (n - 1);
}

void sample_kalman_filter_init_accel(void)
{
	ON_LED_SAMPLE_KALMAN;
	Flash_Erase(EXAMPLE_KALMAN_PAGE_FLASH);

	float sample_data_accel[SAMPLE_SIZE];
	float accel_bias = 0.0f, r = 0.0f, q = 0.0f;

	for(int i = 0; i < SAMPLE_SIZE; i++) {
		mpu_read_accel_axis('x'); 
		sample_data_accel[i] = Accel.xReal;
		delayUs(1000);
	}
	accel_bias = compute_mean(sample_data_accel, SAMPLE_SIZE);
	r = compute_variance(sample_data_accel, SAMPLE_SIZE, accel_bias);
	q = r * 0.01f;
	Flash_Write_32bits(EXAMPLE_KALMAN_PAGE_FLASH, (uint32_t*)&q, 1); 
	Flash_Write_32bits(EXAMPLE_KALMAN_PAGE_FLASH + 4, (uint32_t*)&r, 1);	
	Kalman_init(&kf_x_accel, q, r, 0.0f);

    for(int i = 0; i < SAMPLE_SIZE; i++) {
		mpu_read_accel_axis('y'); 
		sample_data_accel[i] = Accel.yReal;
		delayUs(1000);
	}   
	accel_bias = compute_mean(sample_data_accel, SAMPLE_SIZE);
	r = compute_variance(sample_data_accel, SAMPLE_SIZE, accel_bias);
	q = r * 0.01f;	
	Flash_Write_32bits(EXAMPLE_KALMAN_PAGE_FLASH + 8, (uint32_t*)&q, 1); 
	Flash_Write_32bits(EXAMPLE_KALMAN_PAGE_FLASH + 12, (uint32_t*)&r, 1);	
	Kalman_init(&kf_y_accel, q, r, 0.0f);

    for(int i = 0; i < SAMPLE_SIZE; i++) {
		mpu_read_accel_axis('z'); 
		sample_data_accel[i] = Accel.zReal;
		delayUs(1000);
	}   
	accel_bias = compute_mean(sample_data_accel, SAMPLE_SIZE);
	r = compute_variance(sample_data_accel, SAMPLE_SIZE, accel_bias);
	q = r * 0.01f;
	Flash_Write_32bits(EXAMPLE_KALMAN_PAGE_FLASH + 16, (uint32_t*)&q, 1); 
	Flash_Write_32bits(EXAMPLE_KALMAN_PAGE_FLASH + 20, (uint32_t*)&r, 1);	
	Kalman_init(&kf_z_accel, q, r, 0.0f); 
	OFF_LED_SAMPLE_KALMAN;
}

void kalman_filter_init_accel()
{
	uint8_t check = 0; 

	Flash_Read_32bits(EXAMPLE_KALMAN_PAGE_FLASH, (uint32_t*)tem_kalman, 6); 

	for(int i = 0; i < 6; i++)
		if(tem_kalman[i] == 0xFFFFFFFF) {
			sample_kalman_filter_init_accel(); 
			check = 1; 
			break; 
		}
	if(check == 0) {
		Kalman_init(&kf_x_accel, (float)tem_kalman[0], (float)tem_kalman[1], 0.0f); 
		Kalman_init(&kf_y_accel, (float)tem_kalman[2], (float)tem_kalman[3], 0.0f);
		Kalman_init(&kf_z_accel, (float)tem_kalman[4], (float)tem_kalman[5], 0.0f); 
	}

}

