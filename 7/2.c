#include <stdio.h>
#define LONG_LEN 10
int main()
{
	int c, cc = 0;
	while((c = getchar()) != EOF)
	{
		if(c <= 31 || c == 127)
			printf("%X", c);
		else
			printf("%c", c);
		
		if(++cc == LONG_LEN)		
		{
			printf("\n");
			cc = 0;
		}
	}	
	return 0;
}


