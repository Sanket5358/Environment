#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <semaphore.h>
#include "env_final.h"

int main()
{
    mqd_t mq;
    struct mq_attr attr = {0, 10, sizeof(struct sensor_data), 0};

    mq = mq_open(MQ_NAME, O_CREAT | O_WRONLY, 0666, &attr);

    sem_t *sem_sp = sem_open(SEM_SP, O_CREAT, 0666, 0);
    sem_t *sem_ds = sem_open(SEM_DS, O_CREAT, 0666, 1);

    srand(42);

    struct sensor_data data;

    printf("[Sensor] Started...\n");

    while(1)
    {
        sem_wait(sem_ds);

        data.temperature = rand() % 50;
        data.humidity = rand() % 100;
        data.aqi = rand() % 300;

        mq_send(mq, (char*)&data, sizeof(data), 0);

        printf("[Sensor] Temp=%d Hum=%d AQI=%d\n",
               data.temperature, data.humidity, data.aqi);

        sem_post(sem_sp);
    }
}
