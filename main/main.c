#include <stdio.h>
#include <stdlib.h>
#include "mpu6050.h"

int main() {
    stdio_init_all();
    imu_c imu;
    mpu6050_set_config(&imu, i2c_default, 20, 21, 2);  // Configuração exemplo

    if (mpu6050_init(imu)) {
        printf("MPU6050 inicializado com sucesso.\n");
    } else {
        printf("Erro ao inicializar o MPU6050.\n");
    }

    int16_t accel[3], gyro[3], temp;

    while (1) {

        if (mpu6050_read_acc(imu, accel)) {
            printf("Accel - X: %d, Y: %d, Z: %d\n", accel[0], accel[1], accel[2]);
        } else {
            printf("Erro ao ler o acelerômetro.\n");
        }

        if (mpu6050_read_gyro(imu, gyro)) {
            printf("Giro - X: %d, Y: %d, Z: %d\n", gyro[0], gyro[1], gyro[2]);
        } else {
            printf("Erro ao ler o giroscópio.\n");
        }

        if (mpu6050_read_temp(imu, &temp)) {
            printf("Temp. = %f\n", (temp / 340.0) + 36.53);
        } else {
            printf("Erro ao ler a temperatura.\n");
        }
        sleep_ms(200);
    }
    return 0;
}
