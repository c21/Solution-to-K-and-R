#include <stdio.h>

/* itoa: convert n to characters in s */
void itoa(int n, char s[], int width)
{
	long long i;
	long long sign;
	long long n1 = n;
	if((sign = n1) < 0)
		n1 = -n1;
	i = 0;
	do {
		s[i++] = n1 % 10 + '0';
	} while ((n1 /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';
	
	while(i < width)
	{
		s[i++] = ' ';
	}	
	s[i] = '\0';
	long long j = 0, k = i-1;
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
	int n, w;
	while(scanf("%d%d", &n, &w) == 2)
	{
		itoa(n, s, w);
		printf("s: %s\n", s);
	}	
	return 0;	
}

