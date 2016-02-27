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

10. C, like most languages, does not specify the order in which the operands of  
   an operator are evaluated. (The exceptions are &&, ||, ?:, and ',')

## Chapter 3. Control Flow

1. else is associated with the closest previous else-less if.  
   if (n > 0)  
   &nbsp;&nbsp;if (a > b)  
	&nbsp;&nbsp;&nbsp;&nbsp;	z = a;  
   &nbsp;&nbsp;else  
	&nbsp;&nbsp;&nbsp;&nbsp;	z = b;  
   the else goes with the inner if.

## Chapter 4. Functions and Program Structure 

1. The scope of an external variable or a function lasts from the point at which<br>
   it is declared to the end of the file being compile.

2. extern qualifier: if an external variable is to be referred to before it is<br>
   defined, or if it is defined in a different source file from the one where it is<br>
   being used, then an extern declaration is mandatory.

3. A register declaration advises the compiler that the variable in question<br>
   will be heavily used. The idea is that register variables are to be placed in<br>
   machine registers, which may result in smaller and faster programs. But com-<br>
   pilers are free to ignore the advice.

4. The static declaration, applied to<br> 
   1). an external variable or function, limits the scope of that object to the<br> 
       rest of the source file being compiled.<br>
   2). an internal variable, the variable will remain in existence rather than coming and<br>
       going each time the function is activated.

5. In the absence of explicit initialization, external and static variables are<br>
   guaranteed to be initialized to zero; automatic and register variables have unde-<br>
   fined (i.e., garbage) initial values.

6. \#include "filename", \<filename\>. If the filename is quoted, searching for the file<br>
   typically begins where the source program was found; if it is not found there, or<br> 
   if the name is enclosed in < and >, searching follows an implementation-defined rule<br> 
   to find the file.

7. String literals can be concatenated in C directly.<br>
   char s[] = "4" " 123"; // legal,  s = "4123"

8. macro:<br>
   \#define name replacement text<br>
   1). Normally the replacement text is the rest of the line, but a long defini-<br>
       tion may be continued onto several lines by placing a \ at the end of each line<br>
       to be continued.<br>
   <br>
   \#define f(a, b) replacement text<br>
   Each occurrence of a formal parameter (here a and b) will be replaced by the<br>
   corresponding actual argument.<br>
   1). \#: Formal parameters are not replaced within quoted strings. Only if a<br>
          parameter name is preceded by a \#, the combination will be expanded<br> 
          into a quoted string with the parameter replaced by the actual<br>
          argument.<br>
	  <br>
	  e.g. #define dprint(expr) printf(#expr "=%d\n", expr)<br>
	  dprint(x)  -> printf("x" "=%d\n", x);<br>
	<br>
   2).\#\#: concatenate actual arguments. If a parameter in the replacement text is adja-<br>
          cent to a \#\#, the parameter is replaced by the actual argument, the \#\# and sur-<br>
          rounding white space are removed<br>
	<br>
	  e.g. \#define paste(front, back) front \#\# back<br>
          paste(name, 1)  ->  name1<br>
  
9. conditional inclusion: include code selectively<br>
   1).<br>
   \#if (constant integer expression: defined(xxx))<br>
   &nbsp;&nbsp;   ...<br>
   \#elif ...<br>
   &nbsp;&nbsp;   ...<br>
   \#else<br>
   &nbsp;&nbsp;   ...<br>
   \#endif<br>
 
   2).<br> 
   \#ifndef(\#ifdef) xxx<br>
   ...<br> 
   \#endif 


## Chapter 5. Pointers and Arrays 

1. An array-and-index expression is equivalent to one written<br>
   as a pointer and offset.<br> 
   There is one difference between an array name(a) and a pointer(pa).<br>
   A pointer is a variable, so pa=a and pa++ are legal. But an<br>
   array name is not a variable; a=pa and a++ are illegal.

2. a[-1] is syntactically legal.

3. If p and q point to elements of the same array, and p\<q,<br> 
   then q-p+1 is the number of elements from p to q inclusive.<br>

4. The value of \*t++ is the character that t pointed to<br> 
   before t was incremented.

5. Multi-dimensional array as function's argument or declaration,<br> 
   only the first dimension(subscript) of an array can be not specified;<br> 
   all the others have to be specified.

6. The format argument of printf can be an expression.<br>
   E.g., printf ((argc > 1) ? "%s " : "%s", \*++argv);


## Chapter 6. Structures 

1. The keyword struct introduces a structure declaration, which is a list of<br>
   declarations enclosed in braces. An optional name called a structure tag may<br>
   follow the word struct. The right brace that terminates the list of members<br> 
   may be followed by a list of variables.

2. Both . and -\> associate from left to right.<br>
   These four expressions are equivalent:<br>
   r.pt1.x<br>
   rp-\>pt1.x<br>
   (r.pt1).x<br>
   (rp-\>pt1).x<br>

3. Addition of two pointers is illegal. Subtraction is legal.

4. A simple hash function for string:<br> 
   ``` c 
   unsigned hash(char \*s)<br>
   {
   		unsigned hashval;
   	for (hashval = 0; *s != '\0'; s++)
                hashval = *s + 31 * hashval;
        return hashval % HASHSIZE;
   }
   ```
5. typedef for creating new data type name,<br> 
   typedef int Length<br> 
   In effect, typedef is like \#define, except that since it is interpreted by the compiler,<br>  
   it can cope with textual substitutions that are beyond the capabilities of the<br> 
   preprocessor.<br> 
   main reasons for using typedef:<br> 
   1). The first is to parameterize a program against portability problems.<br> 
       If typedefs are used for data types that may be machine-dependent, only the<br> 
       typedefs need change when the program is moved.<br> 
   2). It may be easier to understand than the true type<br> 

6. bit-field:<br> 
   ``` c
   struct s
   {
		unsigned int f1 : 1;
		unsigned int f2 : 3;
   }x; 
   ```
   x.f1 has 1 bit, x.f2 has 2 bits. But they are not arrays, and they do<br> 
   not have addresses, so the & operator cannot be applied to them.

## Chapter 7. Input and Output


## Chapter 8. The UNIX System Interface 

