#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <stdint.h>

typedef struct {
    float accel_bias[3];
    float gyro_bias[3];
} imu_cal_t;

typedef struct {
    float min[3];
    float max[3];
    float bias[3];
    float scale[3];
} mag_cal_t;

typedef struct {
    float pressure_sum;
    float pressure_ref;
    uint32_t samples;
} baro_cal_t;

void imu_cal_reset(imu_cal_t *cal);
void imu_cal_update(imu_cal_t *cal, const float accel[3], const float gyro[3],
                    uint32_t samples);
void mag_cal_reset(mag_cal_t *cal);
void mag_cal_update(mag_cal_t *cal, const float field[3]);
void mag_cal_finish(mag_cal_t *cal);
void mag_cal_apply(const mag_cal_t *cal, const float raw[3], float out[3]);
void baro_cal_reset(baro_cal_t *cal);
void baro_cal_update(baro_cal_t *cal, float pressure_pa);
float baro_cal_reference(const baro_cal_t *cal);
float baro_altitude_m(float pressure_pa, float sea_level_pa);

#endif
