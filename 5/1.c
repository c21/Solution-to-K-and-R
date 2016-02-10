#include <stdio.h>
#define BUFSIZE 100
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int getch(void)  /* get a (possibly pushed back) character */
{
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  /* push character back on input */
{
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;
}

#include <ctype.h>

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;
	while (isspace(c = getch())) /* skip white space */
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') 
	{
		ungetch(c); /* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	int d;
	if (c == '+' || c == '-' )
	{
		d = getch();
		if(d != EOF)
			ungetch(d);
		if(!isdigit(d))
		{
			ungetch(c);
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main()
{
	int n, array[10];
	for(n = 0; n < 10 && getint(&array[n]) != EOF; n++)
	{
		printf("a: %d\n", array[n]);
	}	
	return 0;
}

