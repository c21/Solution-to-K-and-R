#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
int get_line(char **line);
char* entab(char *line);
int flag = 1;
int TAB_SIZE;

main(int argc, char *argv[])
{
	if(argc == 2)
		TAB_SIZE = strtol(&argv[1][1], NULL, 10);
	else
		TAB_SIZE = 8;

	int len;
	int max;
	char *line;

	while(flag)
	{
		get_line(&line);
		printf("%s", entab(line));
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


char* entab(char *line)
{
	char *p = (char*)malloc(sizeof(char)*(strlen(line)+1));
	memset(p, 0, sizeof(p));
	int i, j = 0, num, k, m, n, q;
	for(i = 0; i < strlen(line); i++)
	{
		if(line[i] != ' ')
		{
			p[j] = line[i];
			j++;
		}
		else
		{
			k = 1;
			q = i+1;
			while(q < strlen(line) && line[q] == ' ')
			{
				q++;
				k++;
			}
			m = TAB_SIZE - (i % TAB_SIZE);
			if(m >= k)
			{
				for(n = 1; n <= k; n++)
				{
					p[j] = ' ';
					j++;
				}
			}		
			else
			{
				k -= m;
				p[j] = '\t';
				j++;
				while(k >= TAB_SIZE)
				{
					p[j] = '\t';
					j++;
					k -= TAB_SIZE;
				}	
				for(n = 1; n <= k; n++)
				{
					p[j] = ' ';
					j++;
				}
			}	
			i = q-1;
		}
	}			
	return p;	
}
