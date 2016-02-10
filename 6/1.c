#include <stdio.h>
#define MAXWORD 10
int getword(char *, int);


main()
{
	int n;
	char word[MAXWORD];
	while (getword(word, MAXWORD) != EOF)
	{
		printf("word:%s\n", word);
	}
	return 0;
}


/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while (isspace(c = getch()))
		;
	if (c != EOF) 
		*w++ = c; 
	if (!isalpha(c) && c != '/') 
	{ 
		*w = '\0'; 
		return c;
	}
	else if(c == '/')
	{
		*w = getch();
		if(*w != '/')
			ungetch(*w);
		else
		{
			for(w++,lim--; --lim > 0; w++)
			{
				if((*w = getch()) == '\n')
					break;
			}
		}	
	}
	else
	{ 
		for (; --lim > 0; w++)
		{
			if (!isalnum(*w = getch()))
			{
				ungetch(*w);
				break;
			}
		}
	}
	*w = '\0';
	return word[0];
}















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


