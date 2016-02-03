/*
Write a function escape (s, t) that converts characters like
newline and tab into visible escape sequences like \n and \t as it copies the
string t to s. Use a switch. Write a function for the other direction as well,
converting escape sequences into the real characters.
*/

void escape(char s[], char t[])
{
	int i = 0, j = 0;
	for(; t[i] != '\0'; i++)
	{
		switch(t[i])
		{
			case '\n': 
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j++] = t[i];	
				break;		
		}	
	}
	s[j] = '\0';		
}

void rev_escape(char s[], char t[])
{
        int i = 0, j = 0;
        for(; t[i] != '\0'; i++)
        {
                switch(t[i])
                {
                        case '\\':
                		if(t[i+1] == 'n')
				{
					s[j++] = '\n';
					i++;
					break;
				}
				else if(t[i+1] == 't')
				{
					s[j++] = '\t';
					i++;
					break;
				}	
			default:
				s[j++] = t[i];
				break;
		}
        }
	s[j] = '\0';
}
