#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int log_fd = open("environment_log.txt",
                      O_CREAT | O_WRONLY | O_APPEND,
                      0666);

    if(log_fd < 0)
    {
        perror("open");
        return 1;
    }

    char buffer[256];

    printf("[Logger] Started...\n");

    while(1)
    {
        int n = read(STDIN_FILENO, buffer, sizeof(buffer));

        if(n > 0)
        {
            write(log_fd, buffer, n);
        }
    }

    close(log_fd);
    return 0;
}
