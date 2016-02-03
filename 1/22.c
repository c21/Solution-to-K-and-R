#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAB_SIZE 8
#define STOP	14
#define MAXLINE 1000
int get_line(char **line);
char* detab(char *line);
void fold(char *line);
int flag = 1;

main()
{
	int len;
	int max;
	char *line;

	while(flag)
	{
		get_line(&line);
		fold(detab(line));
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

void fold(char *line)
{
	int i = 0, len = strlen(line);
	int b = 0, s = -1;
	while(i < len)
	{
		while(i < len && i-b+1 < STOP)
		{
			i++;
			if(line[i] == ' ')
				s = i;	
		}
		if(i == len)
		{
			write(1, &line[b], sizeof(char)*(i-b+1));	
		}			
		else
		{
			if(s == -1)
			{
				write(1, &line[b], sizeof(char)*(i-b));
				if(line[i-1] != '\n')
					printf("\n");
			}	
			else
			{
				if(line[i] == ' ')
				{
					int p = i-1;
					while(p >= b && line[p] == ' ')
						p--;
					if(p >= b)
					{
						write(1, &line[b], sizeof(char)*(p-b+1));
					}		
					if(line[p] != '\n')
						printf("\n");
					i = p+1;
				}
				else
				{
					int p = i-1;
					while(p >= b && line[p] != ' ')
						p--;
					if(p < b)
					{
						write(1, &line[b], sizeof(char)*(i-b));
						if(line[i-1] != '\n')
							printf("\n");
					}
					else
					{
						while(p >= b && line[p] == ' ')
							p--;
						if(p >= b)
						{
							write(1, &line[b], sizeof(char)*(p-b+1));
                                                	if(line[p] != '\n')
                                                        	printf("\n");
							i = p+1;
						}	
					}
				}	
			}
		}
		while(i < len && line[i] == ' ')
                   	i++;
               	b = i;	
		s = -1;
	}				
}
