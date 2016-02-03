/*
Write the function htoi (s ), which converts a string of hexa-
decimal digits (including an optional Ox or ox) into its equivalent integer value.
The allowable digits are 0 through 9, a through f, and A through F
*/
#include <stdio.h>
#include <string.h>

int htoi(char *s)
{
	int len = strlen(s);
	if(len < 1)
		return 0;
	else if(len < 2)
	{
		if(s[0] >= '0' && s[0] <= '9')
			return s[0]-'0';
		else if(s[0] >= 'a' && s[0] <= 'f')
			return s[0]-'a'+10;
		else if(s[0] >= 'A' && s[0] <= 'F')
			return s[0]-'A'+10;	
		else
			return 0;
	}
	int i = ( (s[1] == 'x' || s[1] == 'X') ? 2 : 0);
	int sum = 0, n;
	for(; i < len; i++)
	{
		if(s[i] >= '0' && s[i] <= '9')  
                        n = s[i]-'0';
                else if(s[i] >= 'a' && s[i] <= 'f')
                        n = s[i]-'a'+10;
                else if(s[i] >= 'A' && s[i] <= 'F')
                        n = s[i]-'A'+10;	
		sum = n + sum*16;
	}	
	return sum;	
			
}

main()
{
	char x[100];
	while(scanf("%s", x) != 0)
		printf("%d\n", htoi(x));
	
}
