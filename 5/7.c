#define MAXLEN 1000 /* max length of any input line */
int getline(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int n = 0;
	
	while(n < maxlines && getline(lineptr[n], MAXLEN) > 0)
		n++;
	return n;
}

