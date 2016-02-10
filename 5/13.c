/*
Write the program tail, which prints the last n lines of its
input. By default, n is 10, let us say, but it can be changed by an optional
argument, so that
tail -n
prints the last n lines.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_LEN	100

void tail(int n)
{
	char **buf = (char**)malloc(sizeof(char*)*n);
	int p = -1, c = 0, i, j;
	char line[MAX_LEN+1];
	while(fgets(line, MAX_LEN+1, stdin) != NULL)
	{
		if(line[strlen(line)-1] != '\n')
		{
			fprintf(stderr, "line too long\n");
			exit(1);
		}	
		p = (p+1) % n;
		buf[p] = strdup(line);
		c++;	
	}	
	if(c <= n)
		i = 0;
	else
		i = (p+1) % n;
	for(j = 0; j < n && j < c; j++, i = (i+1)%n)
		printf("%s", buf[i]);				
}


int main(int argc, char *argv[])
{
	char *p;
	long int n;
	if(argc != 2 || argv[1][0] != '-' || (n = strtol(&argv[1][1], &p, 10)) < 0 || n > 30000 || *p != '\0')
	{
		fprintf(stderr, "use: program -n (n <= 30000)\n");
		exit(1);
	}
	tail((int)n);
	return 0;	
			
}
