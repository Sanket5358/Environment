#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int sig)
{
    printf("\n[Supervisor] Shutdown\n");
}

int main()
{
    signal(SIGINT, handler);

    printf("[Supervisor] Starting system...\n");

    int pipefd[2];
    pipe(pipefd);

    if(fork() == 0)
    {
        if(execl("./sensor_final","sensor_final",NULL) == -1)
        {
            perror("sensor");
            exit(1);
        }
    }

    sleep(1);

    if(fork() == 0)
    {
        if(execl("./process_final","process_final",NULL) == -1)
        {
            perror("process");
            exit(1);
        }
    }

    sleep(1);

    if(fork() == 0)
    {
        dup2(pipefd[1], 3);
        close(pipefd[0]);

        if(execl("./display_final","display_final",NULL) == -1)
        {
            perror("display");
            exit(1);
        }
    }

    if(fork() == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);

        if(execl("./logger_final","logger_final",NULL) == -1)
        {
            perror("logger");
            exit(1);
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);

    while(wait(NULL) > 0);

    return 0;
}
