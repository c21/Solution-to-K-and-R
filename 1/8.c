#include <stdio.h>

main()
{
	int bc = 0, tc = 0, nc = 0, c;
	while((c = getchar()) != EOF)
	{
		if(c == ' ')
			bc++;
		else if(c == '\t')
			tc++;
		else if(c == '\n')
			nc++;
	}		
	printf("the number of blanks: %d, tabs: %d, newlines: %d\n", bc, tc, nc);
}
