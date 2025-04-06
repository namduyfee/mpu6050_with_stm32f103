
#ifndef __KALMAN_FILER__
#define __KALMAN_FILER__

#include "main.h"

#define ON_LED_SAMPLE_KALMAN	(GPIOC->ODR &= (~(1 << 13)))
#define OFF_LED_SAMPLE_KALMAN	(GPIOC->ODR |= (1 << 13))

typedef struct {
    float q; // Process noise
    float r; // Measurement noise
    float x; // State
    float p; // Estimation error covariance
    float k; // Kalman gain
} KalmanFilter;

extern KalmanFilter kf_x_accel;
extern KalmanFilter kf_y_accel;
extern KalmanFilter kf_z_accel;

void Kalman_init(KalmanFilter* kf, float q, float r, float initial_value); 
float Kalman_update(KalmanFilter* kf, float measurement); 
float compute_mean(float* data, int n); 
float compute_variance(float* data, int n, float mean); 
void kalman_filter_init_accel(); 

#endif

