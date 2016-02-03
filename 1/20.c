#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAB_SIZE 8
#define MAXLINE 1000
int get_line(char **line);
char* detab(char *line);
int flag = 1;

main()
{
	int len;
	int max;
	char *line;

	while(flag)
	{
		get_line(&line);
		printf("%s", detab(line));
	}
	return 0;			
}

int get_line(char **line)
{
	int c, nowlen = 0, maxlen = MAXLINE, tlen;	
	*line = (char*)malloc(sizeof(char)*MAXLINE);
	while((c = getchar()) != EOF)
	{
		if(nowlen == maxlen)
		{
			maxlen += MAXLINE;
			*line = realloc(*line, maxlen);
		}
		(*line)[nowlen] = c;
		nowlen++;	
		if(c == '\n')
			break;	
	}		

	if(c == EOF)
		flag = 0;
	
	if(nowlen == maxlen)
        {
        	maxlen += MAXLINE;
           	*line = realloc(*line, maxlen);
     	}
     	(*line)[nowlen] = '\0';
	return nowlen;
}


char* detab(char *line)
{
	char *p = (char*)malloc(sizeof(char)*(TAB_SIZE*strlen(line)+1));
	memset(p, 0, sizeof(p));
	int i, j = 0, num, k;
	for(i = 0; i < strlen(line); i++)
	{
		if(line[i] != '\t')
		{
			p[j] = line[i];
			j++;
		}
		else
		{
			num = TAB_SIZE - (j % TAB_SIZE);
			for(k = 1; k <= num; k++)
			{
				p[j] = ' ';
				j++;
			}
		}
	}			
	return p;	
}
