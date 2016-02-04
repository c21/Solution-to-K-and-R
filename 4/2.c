#include <math.h>
#include <stdio.h>
/* atof: convert string s to double */
double atof(char s[])
{
	double val, power, v[2];
	int i = 0, sign, r;
	v[0] = v[1] = 0;
	for(r = 0; r <= 1; r++)
	{
		for(; s[i] == ' ' || s[i] == '\t'; i++)
			;
		sign = (s[i] == '-') ? -1 : 1;
		if(s[i] == '-' || s[i] == '+')
			i++;
		for(val = 0.0; s[i] >= '0' && s[i] <= '9'; i++)
			val = 10.0 * val + (s[i]-'0');
		if(s[i] == '.')
			i++;
		for(power = 1.0; s[i] >= '0' && s[i] <= '9'; i++)
		{
			val = 10.0 * val + (s[i]-'0');
			power *= 10.0;
		}
		v[r] = sign * val / power;
		if(s[i] == 'e' || s[i] == 'E')
                        i++;
		else
			break;
	}
	return v[0] * pow(10.0, v[1]);		
					
}

int main()
{
	char s[100];
	while(scanf("%s", s) != 0)
	{
		printf("%f\n", atof(s));
	}		
	return 0;
}
