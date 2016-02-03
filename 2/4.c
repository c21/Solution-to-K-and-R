
/*Write an alternate version of squeeze (s 1,s2) that deletes
each character in s 1 that matches any character in the string s2.
*/

void squeeze(char* s1, char* s2)
{
	int i, j, k;
	for(i = j = 0; s1[i] != '\0'; i++)
	{
		for(k = 0; s2[k] != '\0'; k++)
		{
			if(s1[i] == s2[k])
			{
				k = -1;
				break;
			}
		}		
		if(k != -1)
		{
			s1[j] = s1[i];
			j++;
		}	
	}		
	s1[j] = '\0';		
}
