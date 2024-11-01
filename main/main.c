/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "mpu6050.h"
#include "pico/stdlib.h"   // Ajuste para a plataforma

int main() {
    stdio_init_all();
    imu_c imu;
    mpu6050_set_config(&imu, i2c0, 4, 5, 2);  // Configuração exemplo

    if (mpu6050_init(imu)) {
        printf("MPU6050 inicializado com sucesso.\n");
    } else {
        printf("Erro ao inicializar o MPU6050.\n");
    }

    int16_t accel[3], gyro[3], temp;

    while (1) {
        if (mpu6050_read_acc(imu, accel)) {
            printf("Acelerômetro - X: %d, Y: %d, Z: %d\n", accel[0], accel[1], accel[2]);
        } else {
            printf("Erro ao ler o acelerômetro.\n");
        }

        if (mpu6050_read_gyro(imu, gyro)) {
            printf("Giroscópio - X: %d, Y: %d, Z: %d\n", gyro[0], gyro[1], gyro[2]);
        } else {
            printf("Erro ao ler o giroscópio.\n");
        }

        if (mpu6050_read_temp(imu, &temp)) {
            printf("Temperatura: %d\n", temp);
        } else {
            printf("Erro ao ler a temperatura.\n");
        }
    }

    return 0;
}
