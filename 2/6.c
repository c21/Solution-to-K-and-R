/*
Write a function setbits(x,p,n,y)
that returns x with the n bits that begin at position p 
set to the rightmost n bits of y, leaving the other
bits unchanged.
*/
#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
//	return ( ( ((x >> (p-n+1)) & (~0 << n)) | (y & ~(~0 << n)) ) << (p-n+1) ) | (x & ~(~0 << (p-n+1)));
	return (x >> (p-n+1) & ~(~0 << n)) | (y & (~0 << n));	
}

