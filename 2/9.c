/*
In a two's complement number system, x &.= (x-1) deletes the
rightmost l-bit in x. Explain why. Use this observation to write a faster ver-
sion of bitcount

Suppose x : yyyy10000...0
      x-1 : yyyy01111...1
  x&(x-1) : yyyy00000...0
*/

int bitcount(unsigned x)
{
	int b;
	for(b = 0; x != 0; x &= (x-1))
		b++;
	return b;
}


