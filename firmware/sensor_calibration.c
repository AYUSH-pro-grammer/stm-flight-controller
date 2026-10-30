#include "sensor_calibration.h"

#define MPU_PWR_MGMT_1  0x6B
#define MPU_ACCEL_XOUT  0x3B
#define MPU_GYRO_CONFIG 0x1B
#define MPU_ACCEL_CONFIG 0x1C
#define LIS_WHO_AM_I    0x0F
#define LIS_CTRL1       0x20
#define LIS_CTRL2       0x21
#define LIS_CTRL3       0x22
#define LIS_OUT_X_L     0x28

static HAL_StatusTypeDef wr(I2C_HandleTypeDef *i2c, uint16_t addr,
                            uint8_t reg, uint8_t val)
{
    return HAL_I2C_Mem_Write(i2c, addr, reg, I2C_MEMADD_SIZE_8BIT,
                             &val, 1, 100);
}

static HAL_StatusTypeDef rd(I2C_HandleTypeDef *i2c, uint16_t addr,
                            uint8_t reg, uint8_t *buf, uint16_t len)
{
    return HAL_I2C_Mem_Read(i2c, addr, reg, I2C_MEMADD_SIZE_8BIT,
                            buf, len, 100);
}

static int16_t be16(uint8_t *p)
{
    return (int16_t)((p[0] << 8) | p[1]);
}

static int16_t le16(uint8_t *p)
{
    return (int16_t)((p[1] << 8) | p[0]);
}

HAL_StatusTypeDef mpu6050_init(I2C_HandleTypeDef *i2c)
{
    HAL_StatusTypeDef st;
    st = wr(i2c, MPU6050_ADDR, MPU_PWR_MGMT_1, 0x00);
    if (st != HAL_OK) return st;
    HAL_Delay(100);
    st = wr(i2c, MPU6050_ADDR, MPU_ACCEL_CONFIG, 0x00);
    if (st != HAL_OK) return st;
    return wr(i2c, MPU6050_ADDR, MPU_GYRO_CONFIG, 0x00);
}

HAL_StatusTypeDef mpu6050_read(I2C_HandleTypeDef *i2c,
                               float accel_g[3], float gyro_dps[3])
{
    uint8_t b[14];
    if (rd(i2c, MPU6050_ADDR, MPU_ACCEL_XOUT, b, sizeof(b)) != HAL_OK)
        return HAL_ERROR;

    for (int i = 0; i < 3; i++)
        accel_g[i] = (float)be16(&b[i * 2]) / 16384.0f;

    for (int i = 0; i < 3; i++)
        gyro_dps[i] = (float)be16(&b[8 + i * 2]) / 131.0f;

    return HAL_OK;
}

HAL_StatusTypeDef lis3mdl_init(I2C_HandleTypeDef *i2c)
{
    uint8_t id;
    if (rd(i2c, LIS3MDL_ADDR, LIS_WHO_AM_I, &id, 1) != HAL_OK)
        return HAL_ERROR;
    if (id != 0x3D) return HAL_ERROR;

    if (wr(i2c, LIS3MDL_ADDR, LIS_CTRL1, 0x70) != HAL_OK) return HAL_ERROR;
    if (wr(i2c, LIS3MDL_ADDR, LIS_CTRL2, 0x00) != HAL_OK) return HAL_ERROR;
    return wr(i2c, LIS3MDL_ADDR, LIS_CTRL3, 0x00);
}

HAL_StatusTypeDef lis3mdl_read(I2C_HandleTypeDef *i2c, float field[3])
{
    uint8_t b[6];
    if (rd(i2c, LIS3MDL_ADDR, LIS_OUT_X_L | 0x80, b, 6) != HAL_OK)
        return HAL_ERROR;

    for (int i = 0; i < 3; i++)
        field[i] = (float)le16(&b[i * 2]);

    return HAL_OK;
}

HAL_StatusTypeDef sensor_imu_calibrate(I2C_HandleTypeDef *i2c,
                                       imu_cal_t *cal, uint16_t samples)
{
    float a[3], g[3], asum[3] = {0}, gsum[3] = {0};
    uint16_t ok = 0;

    if (!samples) return HAL_ERROR;

    for (uint16_t n = 0; n < samples; n++) {
        if (mpu6050_read(i2c, a, g) == HAL_OK) {
            for (int k = 0; k < 3; k++) {
                asum[k] += a[k];
                gsum[k] += g[k];
            }
            ok++;
        }
        HAL_Delay(5);
    }

    if (ok < samples * 0.8f) return HAL_ERROR;

    for (int k = 0; k < 3; k++) {
        cal->accel_bias[k] = asum[k] / ok;
        cal->gyro_bias[k] = gsum[k] / ok;
    }

    cal->accel_bias[2] -= 1.0f;
    return HAL_OK;
}

void sensor_mag_cal_start(mag_cal_t *cal)
{
    mag_cal_reset(cal);
}

void sensor_mag_cal_sample(I2C_HandleTypeDef *i2c, mag_cal_t *cal)
{
    float field[3];
    if (lis3mdl_read(i2c, field) == HAL_OK)
        mag_cal_update(cal, field);
}

void sensor_mag_cal_end(mag_cal_t *cal)
{
    mag_cal_finish(cal);
}
