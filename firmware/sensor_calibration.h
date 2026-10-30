#ifndef SENSOR_CALIBRATION_H
#define SENSOR_CALIBRATION_H

#include "stm32f4xx_hal.h"
#include "calibration.h"

#define MPU6050_ADDR       (0x68U << 1)
#define LIS3MDL_ADDR       (0x1CU << 1)
#define BMP280_ADDR        (0x76U << 1)

typedef struct {
    I2C_HandleTypeDef *i2c;
    imu_cal_t imu;
    mag_cal_t mag;
    baro_cal_t baro;
} sensor_cal_t;

HAL_StatusTypeDef mpu6050_init(I2C_HandleTypeDef *i2c);
HAL_StatusTypeDef mpu6050_read(I2C_HandleTypeDef *i2c,
                               float accel_g[3], float gyro_dps[3]);
HAL_StatusTypeDef lis3mdl_init(I2C_HandleTypeDef *i2c);
HAL_StatusTypeDef lis3mdl_read(I2C_HandleTypeDef *i2c, float field[3]);
HAL_StatusTypeDef sensor_imu_calibrate(I2C_HandleTypeDef *i2c,
                                       imu_cal_t *cal, uint16_t samples);
void sensor_mag_cal_start(mag_cal_t *cal);
void sensor_mag_cal_sample(I2C_HandleTypeDef *i2c, mag_cal_t *cal);
void sensor_mag_cal_end(mag_cal_t *cal);

#endif
