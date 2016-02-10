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
int getfloat(double *pn)
{
	int c, sign;
	while (isspace(c = getch())) /* skip white space */
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') 
	{
		ungetch(c); /* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-' )
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if(c == '.')
	{
		c = getch();
		double x = 0;
		for(; isdigit(c); c = getch())
			x = 10 * x + (c - '0');
		*pn /= x; 
	}	
	if (c != EOF)
		ungetch(c);
	return c;
}

