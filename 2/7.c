/*
Write a function invert(x,p,n)
that returns x with the n bits
that begin at position p inverted (i.e., I changed into 0 and vice versa), leaving
the others unchanged.
*/

unsigned int invert(unsigned int x, int p, int n)
{
	return x ^ ( (~(~0 << n)) << (p-n+1));	
}

