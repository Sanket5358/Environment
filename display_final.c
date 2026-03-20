#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include "env_final.h"

struct sensor_data *shared;
sem_t *sem_pd;
sem_t *sem_ds;

pthread_mutex_t lock;

int pipe_fd = 3;

void* display_thread(void *arg)
{
    while(1)
    {
        sem_wait(sem_pd);

        struct sensor_data local = *shared;

        if(local.temperature < 0)
        {
            sem_post(sem_ds);
            continue;
        }

        pthread_mutex_lock(&lock);

        printf("[Display] Temp=%d Hum=%d AQI=%d\n",
               local.temperature,
               local.humidity,
               local.aqi);
        fflush(stdout);

        dprintf(pipe_fd,
                "[Display] Temp=%d Hum=%d AQI=%d\n",
                local.temperature,
                local.humidity,
                local.aqi);

        if(local.temperature > 40)
        {
            printf("[Display ALERT] High Temperature!\n");
            dprintf(pipe_fd, "[ALERT] High Temperature\n");
        }

        if(local.aqi > 200)
        {
            printf("[Display ALERT] Poor Air Quality!\n");
            dprintf(pipe_fd, "[ALERT] Poor Air Quality\n");
        }

        pthread_mutex_unlock(&lock);

        sem_post(sem_ds);
        sleep(1);
    }
}

int main()
{
    setbuf(stdout, NULL);

    printf("[Display] Started...\n");

    int shm_fd;

    while((shm_fd = shm_open(SHM_NAME, O_RDWR, 0666)) == -1)
        sleep(1);

    shared = mmap(NULL,
                  sizeof(struct sensor_data),
                  PROT_READ,
                  MAP_SHARED,
                  shm_fd,
                  0);

    sem_pd = sem_open(SEM_PD, 0);
    sem_ds = sem_open(SEM_DS, 0);

    pthread_mutex_init(&lock, NULL);

    pthread_t t;
    pthread_create(&t, NULL, display_thread, NULL);
    pthread_join(t, NULL);

    return 0;
}
