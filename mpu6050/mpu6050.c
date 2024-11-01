#include "mpu6050.h"

void mpu6050_set_config(imu_c *config, i2c_inst_t *i2c, int pin_sda, int pin_scl, int acc_scale) {
    config->i2c = i2c;
    config->pin_sda = pin_sda;
    config->pin_scl = pin_scl;
    config->acc_scale = acc_scale;
}

int mpu6050_init(imu_c config) {
    i2c_init(config.i2c, 400 * 1000);  // Configuração de I2C a 400kHz
    gpio_set_function(config.pin_sda, GPIO_FUNC_I2C);
    gpio_set_function(config.pin_scl, GPIO_FUNC_I2C);
    gpio_pull_up(config.pin_sda);
    gpio_pull_up(config.pin_scl);

    uint8_t data = 0x00;
    int result = i2c_write_blocking(config.i2c, MPU6050_ADDR, &data, 1, false);
    return (result == PICO_ERROR_GENERIC) ? 0 : 1;
}

int mpu6050_reset(imu_c config) {
    uint8_t buf[] = {0x6B, 0x00};
    int result = i2c_write_blocking(config.i2c, MPU6050_ADDR, buf, 2, false);
    return (result == PICO_ERROR_GENERIC) ? 0 : 1;
}

int mpu6050_read_acc(imu_c config, int16_t accel[3]) {
    uint8_t buffer[6];
    i2c_write_blocking(i2c_default, MPU6050_ADDR, MPU6050_REG_ACCEL_XOUT_H, 1, true);
    int result = i2c_read_blocking(config.i2c, MPU6050_ADDR, buffer, 6, false);
    if (result == PICO_ERROR_GENERIC) return 0;

    accel[0] = (buffer[0] << 8) | buffer[1];
    accel[1] = (buffer[2] << 8) | buffer[3];
    accel[2] = (buffer[4] << 8) | buffer[5];
    return 1;
}

int mpu6050_read_gyro(imu_c config, int16_t gyro[3]) {
    uint8_t buffer[6];
    i2c_write_blocking(i2c_default, MPU6050_ADDR, MPU6050_REG_GYRO_XOUT_H, 1, true);
    int result = i2c_read_blocking(config.i2c, MPU6050_ADDR, buffer, 6, false);
    if (result == PICO_ERROR_GENERIC) return 0;

    gyro[0] = (buffer[0] << 8) | buffer[1];
    gyro[1] = (buffer[2] << 8) | buffer[3];
    gyro[2] = (buffer[4] << 8) | buffer[5];
    return 1;
}

int mpu6050_read_temp(imu_c config, int16_t *temp) {
    uint8_t buffer[2];
    i2c_write_blocking(i2c_default, MPU6050_ADDR, MPU6050_REG_TEMP_OUT_H, 1, true);
    int result = i2c_read_blocking(config.i2c, MPU6050_ADDR, buffer, 2, false);
    if (result == PICO_ERROR_GENERIC) return 0;

    *temp = (buffer[0] << 8) | buffer[1];
    return 1;
}
