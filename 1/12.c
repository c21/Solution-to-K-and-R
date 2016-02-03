#include <stdio.h>

main()
{
	int c;
	while((c = getchar()) != EOF)
	{
		if(c != ' ' && c != '\t' && c != '\n')
		{
			putchar(c);
			while((c = getchar()) != EOF)
			{
				if(c == ' ' || c == '\t' || c == '\n')
					break;
				else
					putchar(c);
			}
			putchar('\n');
			if(c == EOF)
				break;
		}	
	}	
}
