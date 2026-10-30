#include "sensor_calibration.h"

extern I2C_HandleTypeDef hi2c1;

imu_cal_t imu_cal;
mag_cal_t mag_cal;

void sensors_startup_calibration(void)
{
    mpu6050_init(&hi2c1);
    lis3mdl_init(&hi2c1);

    sensor_imu_calibrate(&hi2c1, &imu_cal, 500);
    sensor_mag_cal_start(&mag_cal);
}

void sensors_mag_calibration_step(void)
{
    sensor_mag_cal_sample(&hi2c1, &mag_cal);
}

void sensors_mag_calibration_save(void)
{
    sensor_mag_cal_end(&mag_cal);
}

void imu_get_corrected(float accel[3], float gyro[3])
{
    for (int i = 0; i < 3; i++) {
        accel[i] -= imu_cal.accel_bias[i];
        gyro[i] -= imu_cal.gyro_bias[i];
    }
}
