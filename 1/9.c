#include <stdio.h>

main()
{
	int c;
	while((c = getchar()) != EOF)
	{
		if(c == ' ')
		{
			putchar(c);
			while((c = getchar()) == ' ')
				;
			if(c == EOF)
				break;
			else
				putchar(c);
		}
		else
			putchar(c);
	}		
}
