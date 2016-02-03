#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 10

int get_line(char **line);
void reverse(char *s);

int flag = 1;

main()
{
	int len;
	int max;
	char *line;

	while(flag)
	{
		get_line(&line);
		reverse(line);
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
	return nowlen;
}

void reverse(char *s)
{
	int len = strlen(s), i;
	char tmp;
	if(len > 0 && s[len-1] == '\n')
		len--;
	for(i = 0; i <= (len-1)/2; i++)
	{
		tmp = s[i];
		s[i] = s[len-1-i];
		s[len-1-i] = tmp;
	}		
}
