/*
Write a program that converts upper case to lower or lower case
to upper, depending on the name it is invoked with, as found in argv [ 0 ].
*/

#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	char *p = &(argv[0][2]);
	int c, flag;
	if(strcmp(p, "tolower") == 0)
		flag = 1;
	else if(strcmp(p, "toupper") == 0)
		flag = -1;
	else
		flag = 0;
	if(flag == 0)
		return 1;
	while((c = getchar()) != EOF)
		putchar(flag == 1 ? tolower(c) : toupper(c));
	return 0;
}
