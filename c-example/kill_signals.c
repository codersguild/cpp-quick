#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <unistd.h>

#define VALID 3165

int is_valid_fd(int fd)
{
    return fcntl(fd, F_GETFL) != -1 || errno != EBADF;
}

void handle_sigint(int sig)
{
    printf("\n\nSUCCESS\n\n");
    exit(0);
}

int main()
{

    if (is_valid_fd(VALID))
    {
        write(VALID, "Send me user defined signal 2\n", 31);
        printf("Current PID : %ld, Parent PID %ld \n", (long)getpid(), (long)getppid());
        signal(SIGUSR2, handle_sigint);
    }
    else
    {
        printf("ERROR : Redirect Output to [fd] you got from previous part\n");
        exit(-1);
    }

    while (1)
    {
        sleep(1);
        write(2, "\n\nKILL ME with SUCCESS\n\n", 250);
    }

    return 0;
}
