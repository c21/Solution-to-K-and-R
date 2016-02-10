/*
Write versions of the library functions strncpy, strncat, and
strncmp; which operate on at most the first n characters of their argument
strings. For example, strncpy ( s,t ,n) copies at most n characters of t to s.
Full descriptions are in Appendix B.
*/
#include <stdio.h>

char* strncpy(char *s, char *t, int n)
{
	int i = 0;
	char *p = s;
	while(*t != '\0' && i < n)
	{
		*s = *t;
		s++;
		t++;
		i++;	
	}	
	if(i < n)
		*s = *t;
	return p;		
}  


int main()
{
	char s[100], t[100];
	int n;
	while(scanf("%s %s %d", s, t, &n) != 0)
	{
		printf("%s\n", strncpy(s, t, n));
	}
	return 0;
} 
