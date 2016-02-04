/*
Write a recursive version of the function reverse(s),
which reverses the string s in place.
*/
#include <stdio.h>
#include <string.h>

void reverse(char *s)
{
	int j = strlen(s)-1;
	if(j <= 0)
		return;	
	char c1 = s[0], c2 = s[j];
	if(j >= 2)
	{
		s[j] = '\0';
		reverse(s+1);
	}	
	s[0] = c2;
	s[j] = c1;
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
