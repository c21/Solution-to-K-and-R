#include <stdio.h>
/*
Write a pointer version of the function strcat that we showed
in Chapter 2: strcat(s,t) copies the string t to the end of s.
*/
void strcat(char *s, char *t)
{
	while(*s != '\0')
		s++;
	while((*s++ = *t++) != '\0')
		;		
}

int main()
{
	char s[100], t[100];
	while(scanf("%s %s", s, t) != 0)
	{
		printf("s: %s, t: %s\n", s, t);
		strcat(s, t);
		printf("after s: %s, t: %s\n", s, t);
	}
	return 0;
}
