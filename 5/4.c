/*
Write the function strend (s,t), which returns 1 if the string
t occurs at the end of the string s, and zero otherwise
*/
#include <stdio.h>

int strend(char *s, char *t)
{
	char *p1 = s, *p2 = t;
	while(*s != '\0')
		s++;
	while(*t != '\0')
		t++;
	while(t != p2-1)
	{
		if(*s != *t)
			return 0;
		t--;
		s--;
		if(s == p1-1 && t != p2-1)
			return 0;
	}			
	return 1;		
}

int main()
{
	char s[100], t[100];
	while(scanf("%s %s", s, t) != 0)
	{
		printf("%d\n", strend(s, t));
	}
	return 0;
}
