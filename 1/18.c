#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 10

int get_line(char **line);
int flag = 1;

main()
{
	int len;
	int max;
	char *line;

	while(flag)
	{
		len = get_line(&line);
		if(len > 0)
			printf("%s", line);
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
	tlen = (c == '\n' ? nowlen-2 : nowlen-1);
	
	while(tlen >= 0)
	{
		if((*line)[tlen] == ' ' || (*line)[tlen] == '\t')
			tlen--;
		else
			break;
	}
	if(tlen < 0)
		return 0;
	else
	{
		if(c == '\n')
		{
			tlen++;
			(*line)[tlen] = '\n';
		}
		tlen++;
		(*line)[tlen] = '\0';
		return tlen;	
	}
}

