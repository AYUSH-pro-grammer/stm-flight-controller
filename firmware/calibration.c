#include "calibration.h"
#include <string.h>
#include <math.h>

void imu_cal_reset(imu_cal_t *cal)
{
    memset(cal, 0, sizeof(*cal));
}

void imu_cal_update(imu_cal_t *cal, const float accel[3], const float gyro[3],
                    uint32_t samples)
{
    static float a_sum[3], g_sum[3];
    static uint32_t count;

    if (samples == 0) {
        memset(a_sum, 0, sizeof(a_sum));
        memset(g_sum, 0, sizeof(g_sum));
        count = 0;
        return;
    }

    for (int i = 0; i < 3; i++) {
        a_sum[i] += accel[i];
        g_sum[i] += gyro[i];
    }
    count++;

    if (count >= samples) {
        for (int i = 0; i < 3; i++) {
            cal->accel_bias[i] = a_sum[i] / count;
            cal->gyro_bias[i] = g_sum[i] / count;
        }
        cal->accel_bias[2] -= 1.0f;
        memset(a_sum, 0, sizeof(a_sum));
        memset(g_sum, 0, sizeof(g_sum));
        count = 0;
    }
}

void mag_cal_reset(mag_cal_t *cal)
{
    for (int i = 0; i < 3; i++) {
        cal->min[i] = 1.0e9f;
        cal->max[i] = -1.0e9f;
        cal->bias[i] = 0.0f;
        cal->scale[i] = 1.0f;
    }
}

void mag_cal_update(mag_cal_t *cal, const float field[3])
{
    for (int i = 0; i < 3; i++) {
        if (field[i] < cal->min[i]) cal->min[i] = field[i];
        if (field[i] > cal->max[i]) cal->max[i] = field[i];
    }
}

void mag_cal_finish(mag_cal_t *cal)
{
    float radius[3];
    float avg = 0.0f;

    for (int i = 0; i < 3; i++) {
        cal->bias[i] = (cal->max[i] + cal->min[i]) * 0.5f;
        radius[i] = (cal->max[i] - cal->min[i]) * 0.5f;
        avg += radius[i];
    }

    avg /= 3.0f;
    for (int i = 0; i < 3; i++) {
        cal->scale[i] = radius[i] > 0.0f ? avg / radius[i] : 1.0f;
    }
}

void mag_cal_apply(const mag_cal_t *cal, const float raw[3], float out[3])
{
    for (int i = 0; i < 3; i++)
        out[i] = (raw[i] - cal->bias[i]) * cal->scale[i];
}

void baro_cal_reset(baro_cal_t *cal)
{
    cal->pressure_sum = 0.0f;
    cal->pressure_ref = 0.0f;
    cal->samples = 0;
}

void baro_cal_update(baro_cal_t *cal, float pressure_pa)
{
    if (pressure_pa < 30000.0f || pressure_pa > 120000.0f) return;
    cal->pressure_sum += pressure_pa;
    cal->samples++;
    cal->pressure_ref = cal->pressure_sum / cal->samples;
}

float baro_cal_reference(const baro_cal_t *cal)
{
    return cal->samples ? cal->pressure_ref : 101325.0f;
}

float baro_altitude_m(float pressure_pa, float sea_level_pa)
{
    if (pressure_pa <= 0.0f || sea_level_pa <= 0.0f) return 0.0f;
    return 44330.0f * (1.0f - powf(pressure_pa / sea_level_pa, 0.19029495f));
}
