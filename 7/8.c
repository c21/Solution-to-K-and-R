#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 1000

int main(int argc, char *argv[])
{
    int i, count = 1;
    char buf[MAX_LEN];
    for(i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if(fp == NULL)
            continue;
        printf("file%d:\n", count++);
        while(fgets(buf, MAX_LEN, fp) != NULL)
            printf("%s", buf);
        fclose(fp);      
    }
    return 0; 
}
