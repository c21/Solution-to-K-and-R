#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 1000

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "usage: program a b\n");
        exit(1);
    } 
    FILE *fp1, *fp2;
    if((fp1 = fopen(argv[1], "r")) == NULL || (fp2 = fopen(argv[2], "r")) == NULL)
    {
        fprintf(stderr, "open file error\n");
        exit(1);
    }  
    char buf1[MAX_LEN], buf2[MAX_LEN];
    char *p1, *p2;
    p1 = fgets(buf1, MAX_LEN, fp1);
    p2 = fgets(buf2, MAX_LEN, fp2);
    while(p1 != NULL && p2 != NULL)
    {
        if(strcmp(buf1, buf2) != 0)
            break;
        p1 = fgets(buf1, MAX_LEN, fp1);
        p2 = fgets(buf2, MAX_LEN, fp2);
    }     
    if(p1 != NULL)
        printf("1: %s", buf1);
    if(p2 != NULL)
        printf("2: %s", buf2);
    return 0;
}
