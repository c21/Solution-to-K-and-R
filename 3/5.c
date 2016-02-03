/*
Write the function itob(n, s ,b) that converts the integer n
into a base b character representation in the string s. In particular,
itob( n, s, 16) formats n as a hexadecimal integer in s.
*/
#include <stdio.h>

void itob(int n, char *s, int b)
{
	long long n1 = n;
	long long sign = 1, i = 0;
	if(n1 < 0)
	{
		n1 = -n1;
		sign = -1;
	}		
	do
	{
		long long r = n1 % b;
		if(r >= 10)
			s[i] = (r-10+'A');
		else
			s[i] = r+'0';
		i++;
		n1 = n1 / b;				
	}while(n1 > 0);
	if(sign < 0)
	{
		s[i] = '-';
		i++;
	}
	s[i] = '\0';
	long long j = 0, k = i-1;;
	for(; j < k; j++, k--)
	{
		char tmp = s[j];
		s[j] = s[k];
		s[k] = tmp;
	}
}


int main()
{
	char s[100];
	int n, b;
	while(scanf("%d%d", &n, &b) == 2)
	{
		itob(n, s, b);
		printf("s: %s\n", s);
	}	
	return 0;
}
