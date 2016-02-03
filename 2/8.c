/*
Write a function rightrot(x,n)
that returns the value of the
integer x rotated to the right by n bit positions
*/

unsigned int rightrot(unsigned int x, int n)
{
	n = n % (sizeof(x)*8);
	return (x >> n) || (x << (sizeof(x)*8-n));		
}

