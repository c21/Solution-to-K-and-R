#include <stdio.h>
#include <string.h>
#define MAXLINES 5000	/* max #lines to be sorted */
char *lineptr[MAXLINES];/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right, int (*comp) (void *, void *));
int numcmp(char *, char *);
int inc;
int fold;
int direct;
int field;

/* sort input lines */
main(int argc, char *argv[])
{
	int nlines, i;	/* number of input lines read */
	int numeric = 0;/* 1 if numeric sort */
	inc = 1;	/* 1 if incresing sort */
	fold = 0;	/* 1 if fold */
	direct = 0;
	field = 0;
	char *p;

	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-n") == 0)
			numeric = 1;
		else if(strcmp(argv[i], "-r") == 0)
			inc = -1;
		else if(strcmp(argv[i], "-f") == 0)
                        fold = 1;
		else if(strcmp(argv[i], "-d") == 0)
			direct = 1;
		else if(strcmp(argv[i], "-e") == 0)
		{
			if(i+1 == argc || ((field = strtol(argv[i+1], &p, 10)) <= 0) || *p != '\0')
			{
				fprintf(stderr, "wrong parameter");
				return 1;
			}
			i++;
		}
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

char* foldup(char *s);
char* filter(char *s);
char* get_field(char *s, int n);

/* qsort: sort v[left] ...v[right] into increasing order */
void qsort(void *v[], int left, int right, int (*comp) (void *, void *))
{
	int i, last;
	void *v1, *v2;
	void swap(void *v[], int, int);
	if (left >= right)	/* do nothing if array contains */
		return;		/* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
	{
		v1 = v[i], v2 = v[left];
		if(field)
		{
			v1 = get_field(v1, field);
			v2 = get_field(v2, field);
		}
		if(direct)
		{
			v1 = filter(v1);
			v2 = filter(v2);
		}
		if(fold)
		{
			v1 = foldup(v1);
			v2 = foldup(v2);
		}
		if ((*comp)(v1, v2)*inc < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qsort(v, left, last-1, comp);
	qsort(v, last+1, right, comp);
}

char* foldup(char *s)
{
	char *p = strdup(s);
	int i = 0;
	while(p[i] != '\0')
	{
		if(p[i] >= 'A' && p[i] <= 'Z')
			p[i] = p[i] - 'A' + 'a';
		i++;
	}	
	return p;	
}

char* filter(char *s)
{
	char *p = strdup(s);
	int i = 0, j = 0;
	while(s[j] != '\0')
	{
		if(s[j] == ' ' || s[j] == '\t' || (s[j] >= '0' && s[j] <= '9') || (s[j] >= 'a' && s[j] <= 'z')
			|| (s[j] >= 'A' && s[j] <= 'Z'))
		{
			p[i++] = s[j++];
		}
		else
			j++;	
	}		
	p[i] = '\0';
	return p;	
}

char* get_field(char *s, int n)
{
	char *buf = strdup(s), *p = strdup(s), *q;
	int i = 0;
	q = strtok(buf, " \t");
	while(q != NULL && i < n)
	{
		p = strdup(q);
		q = strtok(NULL, " \t");
		i++;
	}
	return p;	
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


