#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_SIZE 1000

main()
{
	int *lc = (int*)malloc(sizeof(int)*LEN_SIZE);
	memset(lc, 0, sizeof(lc));
	int lsize = LEN_SIZE;
	int c, len = 0, i, j;
	int maxlen = 0, maxc = 0;
	
	while((c = getchar()) != EOF)
	{
		if(c != ' ' && c != '\t' && c != '\n')
		{
			len = 1;
			while((c = getchar()) != EOF)
			{
				if(c == ' ' || c == '\t' || c == '\n')
					break;
				else
					len++;
			}
		
			if(len >= lsize)
			{
				lc = realloc(lc, len+1);
				for(i = lsize; i <= len; i++)
					lc[i] = 0;
				lsize = len+1;	
			}
			lc[len]++;
			maxc = lc[len] > maxc ? lc[len] : maxc;
			maxlen = len > maxlen ? len : maxlen;

			if(c == EOF)
				break;			
		}	
	}			

	for(i = maxc; i >= 1; i--)
	{
		for(j = 1; j <= maxlen; j++)
		{
			if(lc[j] != 0)
			{
				if(lc[j] >= i)
					printf("     |");
				else
					printf("      ");
			}
		}
		printf("\n");
	}
	for(i = 1; i <= maxlen; i++)
	{
		if(lc[i] != 0)
			printf("%6d", i);
	}
	if(maxc > 0)	
		printf("\n");
}
