/*
Write a function expand (s1, s2) that expands shorthand nota-
tions like a-z in the string s1 into the equivalent complete list abc...xyz in
s2. Allow for letters of either case and digits, and be prepared to handle cases
like a-b-c and a-zO-9 and -a-z. Arrange that a leading or trailing - is
taken literally.
*/
#include <stdio.h>

// assume expand a-a to a-a, and 0-0 to 0-0
void expand(char *s1, char *s2)
{
	int p1 = 0, p2 = 0;
	for(; s1[p1] != '\0'; p1++)
	{
		if(s1[p1] >= 'a' && s1[p1] <= 'z')
		{
			int k = p1;
			while(s1[k+1] == '-' && s1[k+2] > s1[k] && s1[k+2] <= 'z')
				k += 2;
			int i;
			for(i = s1[p1]; i <= s1[k]; i++)
			{
				s2[p2] = i;
				p2++;
			}
			p1 = k;			
		}
		else if(s1[p1] >= 'A' && s1[p1] <= 'Z')
		{
			int k = p1;
                        while(s1[k+1] == '-' && s1[k+2] > s1[k] && s1[k+2] <= 'Z')
                                k += 2;
                        int i;  
                        for(i = s1[p1]; i <= s1[k]; i++)
                        {
                                s2[p2] = i;
                                p2++;
                        }
                        p1 = k;	
		}	
		else if(s1[p1] >= '0' && s1[p1] <= '9')
                {
                        int k = p1;
                        while(s1[k+1] == '-' && s1[k+2] > s1[k] && s1[k+2] <= '9')
                                k += 2;
                        int i;
                        for(i = s1[p1]; i <= s1[k]; i++)
                        {
                                s2[p2] = i;
                                p2++;
                        }
                        p1 = k;
                }
		else
		{
			s2[p2] = s1[p1];
			p2++;
		}
	}	
	s2[p2] = '\0';	
}


int main()
{
	char s1[100], s2[100];
	while(scanf("%s",s1) != 0)
	{
		expand(s1, s2);
		printf("s2: %s\n", s2);		
	}	
	return 0;
}
