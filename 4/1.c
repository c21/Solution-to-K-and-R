/*
Write the function strrindex
(s, t), which returns the position
of the rightmost occurrence of t in s, or - 1 if there is none
*/
#include <stdio.h>

int strrindex(char *s, char *t)
{
	int p1, p2, idx = -1;
	for(p1 = 0; s[p1] != '\0'; p1++)
	{
		for(p2 = 0; s[p1+p2] != '\0'&& t[p2] != '\0' && s[p1+p2] == t[p2]; p2++)
			;
		if(t[p2] == '\0')
			idx = p1;
		else if(s[p1+p2] == '\0')
			break;	
	}		
	return idx;
}

int main()
{
	char s[100], t[100];
	while(scanf("%s%s", s, t) != 0)
	{
		printf("%d\n", strrindex(s, t));
	}	
	return 0;
}
