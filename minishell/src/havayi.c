#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>

int main()
{
    int fd = open("env.c", O_RDONLY);
    printf("fd = %d\n", fd);
    printf("%s", ttyname(2));
}