/*
Write a recursive version of the function reverse(s),
which reverses the string s in place.
*/
#include <stdio.h>

void reverse(char *s)
{
	char *p = s;
	while(*p != '\0')
		p++;
	p--;
	for(; s < p; s++,p--)
	{
		char tmp = *s;
		*s = *p;
		*p = tmp;
	}			
}


int main()
{
	char s[100];
	while(scanf("%s", s) != 0)
	{
		reverse(s);
		printf("s: %s\n", s);
	}	
	return 0;
}
