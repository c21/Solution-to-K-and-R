# Solution to K and R

This repo is my (ugly) solution to exercises in K&R book
(https://en.wikipedia.org/wiki/The_C_Programming_Language). 

and some (random) notes...

## Chapter 1. A Tutorial Introduction 

1. printf("%3.2f", x);
   %a.bf: print a floating point number, with width a, b digits after decimal point

2. assignment a = b+c has a value, which is the value of left hand side after assignment

3. EOF(end of file) is -1

4. char is just small integer, '0' is essentially an integer number

5. in C, function's argument is call by value

6. when using external variable, one should use "extern" to make variable declaration
   definition: variable is created or assigned storage
   declaration: no storage is allocated   

7. the default return value type of function is int


## Chapter 2. Types, Operators, and Expressions

1. External and static variables are initialized to zero by default.

2. short, long, signed, unsigned are qualifiers 

3. The standard header <ctype.h> defines a family of functions that 
   provide tests and conversionsthat are independent of character
   set. e.g. tolower(), isdigit()

4. The expression ++n increments n before its value is used, while 
   n++ increments n after its value has been used
   1)
   n = 5;
   x = n++;	// x = 5, n = 6
   2)
   n = 5; 
   x = ++n;	// x = 6, n = 6

5. The unary operator ~ yields the one's complement of an integer.
   That is, it converts each 1-bit into a O-bit and vice versa.

6. Right shifting an unsigned quantity always fills vacated bits with zero. 
   Right shifting a signed quantity will fill with sign bits 
   ("arithmetic shift") on some machines and with O-bits ("logical shift") 
   on others.

7. expr1 op= expr2  is equivalent to expr1 = (expr1) op (expr2)
   x *= y+1 is equivalent to x = x * (y+1)

8. The conditional expression expr1 ? expr2 : expr3
   Only one of expr2 and expr3 is evaluated.
 
9. sizeof is an operator

10.C, like most languages, does not specify the order in which the operands of
   an operator are evaluated. (The exceptions are &&, ||, ?:, and ',')
