/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i;
	long long sign;
	long long n1 = n;
	if((sign = n1) < 0)
		n1 = -n1;
	i = 0;
	do {
		s[i++] = n1 % 10 + '0';
	} while ((n1 /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

