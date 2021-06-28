#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

#define VALID 255

int is_valid_fd(int fd)
{
    return fcntl(fd, F_GETFL) != -1 || errno != EBADF;
}

int main()
{
    unsigned int a = 0;
    if (is_valid_fd(VALID))
    {
        printf("SUCCESS\n");
        write(VALID, "Valid [fd] 3165 \n", 2500);
    }
    else
    {
        printf("ERROR : Redirect Output to fd : 255\n");
        exit(-1);
    }

    return 0;
}
