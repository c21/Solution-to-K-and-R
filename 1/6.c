#include <stdio.h>

main()
{
	int c;
	while(c = getchar() != EOF)
	{
		printf("c:%d\n", c);
		putchar(c);
	}
	printf("c: %d\n", c);
}
