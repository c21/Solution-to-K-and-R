#include <stdio.h>

main()
{
	int fc[12], maxc = 0;	
	int c, i, j;

	for(i = 0; i < 12; i++)
		fc[i] = 0;

	while((c = getchar()) != EOF)
	{
		if(c >= '0' && c <= '9')
		{
			fc[c-'0']++;
			maxc = fc[c-'0'] > maxc ? fc[c-'0'] : maxc;
		}
		else if(c == ' ' || c == '\t' || c == '\n')
		{
			fc[10]++;
			maxc = fc[10] > maxc ? fc[10] : maxc;
		}
		else
		{
			fc[11]++;		
			maxc = fc[11] > maxc ? fc[11] : maxc;
		}	
	}	

	for(i = maxc; i >= 1; i--)
	{
		for(j = 0; j < 12; j++)
		{
			if(fc[j] >= i)
				printf("     |");
			else
				printf("      ");
		}
		printf("\n");	
	}			
	for(i = 0; i < 12; i++)
	{
		if(i == 10)
			printf(" blank");
		else if(i == 11)
			printf(" other");
		else
			printf("%6d", i);
	}
	printf("\n");
	
}
