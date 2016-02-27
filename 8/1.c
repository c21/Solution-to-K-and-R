/*
Rewrite the program cat from Chapter 7 using read, write,
open and close instead of their standard library equivalents. Perform experi-
ments to determine the relative speeds of the two versions
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE    1024
int main(int argc, char *argv[])
{
    int i, n;
    char buf[BUF_SIZE];
    for(i = 1; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY, 0);
        if(fd == -1)
            continue;
        while((n = read(fd, buf, BUF_SIZE)) > 0)
        {
            if(write(1, buf, n) != n)
            {
                fprintf(stderr, "output error\n");
                exit(1);
            }
        }      
    } 
    return 0;
}
