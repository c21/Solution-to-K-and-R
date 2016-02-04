#include <string.h>
#include <stdio.h>
/*
Adapt the ideas of printd to write a recursive version of itoa;
that is, convert an integer into a string by calling a recursive routine.
*/
void itoa(int n, char s[])
{
	long long i, n1 = n;
	if(n1 < 0)
	{
		n1 = -n1;
		s[0] = '-';
		s[1] = '\0';
	}
	char r = (n1 % 10) + '0';
	if(n1 >= 10)
		itoa(n1/10, s);
	int len = strlen(s);
	s[len] = r;
	s[len+1] = '\0';				
}

int main()
{
	char s[100];
	int n;
	while(scanf("%d", &n) != 0)
	{
		memset(s, 0, sizeof(s));
		itoa(n, s);
		printf("s: %s\n", s);
	}
	return 0;
}
