#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 10

int get_line(char **line);
void copy(char **to, char from[]);

main()
{
	int len;
	int max;
	char *line;

	while((len = get_line(&line)) > 0)
	{
		if(len > 80)
			printf("%s", line);
	}
	return 0;			
}

int get_line(char **line)
{
	int c, nowlen = 0, maxlen = MAXLINE;	
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
	
	if(nowlen == maxlen)
        {
        	maxlen += MAXLINE;
           	*line = realloc(*line, maxlen);
     	}
     	(*line)[nowlen] = '\0';
	return nowlen;    
}

