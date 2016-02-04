#include <stdio.h>

#define swap(t,x,y)	{ \
				t tmp = (x);	\
				(x) = (y);	\
				(y) = tmp;	\
			}

#define print(x,y)	printf(#x ": %d " #y ": %d\n", x, y);

int main()
{
	int x = 1, y = 2;
	int tmp = 3;
	swap(int, x, y)
	print(x,y)
	printf("tmp: %d\n", tmp);
	return 0;	
}	 
