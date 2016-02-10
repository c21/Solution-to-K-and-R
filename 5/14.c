#include <stdio.h>
#include <string.h>

#define MAXLINES 5000	/* max #lines to be sorted */
char *lineptr[MAXLINES];/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right, int (*comp) (void *, void *));
int numcmp(char *, char *);
int inc;

/* sort input lines */
main(int argc, char *argv[])
{
	int nlines, i;	/* number of input lines read */
	int numeric = 0;/* 1 if numeric sort */
	inc = 1;	/* 1 if incresing sort*/

	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-n") == 0)
			numeric = 1;
		else if(strcmp(argv[i], "-r") == 0)
			inc = -1;
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) 
	{
		qsort(	(void **)lineptr, 0, nlines-1,
			(int (*)(void*,void*))(numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	} 
	else 
	{
		printf("input too big to sort\n");
		return 1;
	}
}

/* qsort: sort v[left] ...v[right] into increasing order */
void qsort(void *v[], int left, int right, int (*comp) (void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);
	if (left >= right)	/* do nothing if array contains */
		return;		/* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left])*inc < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1, comp);
	qsort(v, last+1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;
	
	v1 = atoi(s1);
	v2 = atoi(s2);
	
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}


#define MAXLEN 1000 /* max length of any input line */
int mygetline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = mygetline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else 
		{
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/* getline: get line into s, return length */
int mygetline(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

#define ALLOCSIZE 10000		/* size of available space */
static char allocbuf[ALLOCSIZE];/* storage for alloc */	
static char *allocp = allocbuf; /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) 
	{ /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	} 
	else /* not enough room */
		return 0;
}


