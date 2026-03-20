#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include "env_final.h"

int main()
{
    mqd_t mq;

    while((mq = mq_open(MQ_NAME, O_RDONLY)) == -1)
        sleep(1);

    printf("[Processor] Started...\n");

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(struct sensor_data));

    struct sensor_data *shared = mmap(NULL,
                                      sizeof(struct sensor_data),
                                      PROT_READ | PROT_WRITE,
                                      MAP_SHARED,
                                      shm_fd,
                                      0);

    shared->temperature = -1;
    shared->humidity = -1;
    shared->aqi = -1;

    sem_t *sem_sp = sem_open(SEM_SP, O_CREAT, 0666, 0);
    sem_t *sem_pd = sem_open(SEM_PD, O_CREAT, 0666, 0);

    struct sensor_data data;

    while(1)
    {
        sem_wait(sem_sp);

        mq_receive(mq, (char*)&data, sizeof(data), NULL);

        *shared = data;

        printf("[Processor] Temp=%d Hum=%d AQI=%d\n",
               data.temperature, data.humidity, data.aqi);

        sem_post(sem_pd);
    }
}
