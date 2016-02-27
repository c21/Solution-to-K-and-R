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
   &nbsp;if (a > b)  
	&nbsp;&nbsp;	z = a;  
   &nbsp;else  
	&nbsp;&nbsp;	z = b;  
   the else goes with the inner if.

## Chapter 4. Functions and Program Structure 

1. The scope of an external variable or a function lasts from the point at which<br>
   it is declared to the end of the file being compile.

2. extern qualifier: if an external variable is to be referred to before it is
   defined, or if it is defined in a different source file from the one where it is
   being used, then an extern declaration is mandatory.

3. A register declaration advises the compiler that the variable in question
   will be heavily used. The idea is that register variables are to be placed in
   machine registers, which may result in smaller and faster programs. But com-
   pilers are free to ignore the advice.

4. The static declaration, applied to 
   1). an external variable or function, limits the scope of that object to the 
       rest of the source file being compiled.
   2). an internal variable, the variable will remain in existence rather than coming and
       going each time the function is activated.

5. In the absence of explicit initialization, external and static variables are
   guaranteed to be initialized to zero; automatic and register variables have unde-
   fined (i.e., garbage) initial values.

6. #include "filename", <filename>. If the filename is quoted, searching for the file 
   typically begins where the source program was found; if it is not found there, or 
   if the name is enclosed in < and >, searching follows an implementation-defined rule 
   to find the file.

7. String literals can be concatenated in C directly.
   char s[] = "4" " 123"; // legal,  s = "4123"

8. macro:
   #define name replacement text
   1). Normally the replacement text is the rest of the line, but a long defini-
       tion may be continued onto several lines by placing a \ at the end of each line
       to be continued.
  
   #define f(a, b) replacement text
   Each occurrence of a formal parameter (here a and b) will be replaced by the
   corresponding actual argument.
   1). #: Formal parameters are not replaced within quoted strings. Only if a
          parameter name is preceded by a #, the combination will be expanded 
          into a quoted string with the parameter replaced by the actual
          argument.

	  e.g. #define dprint(expr) printf(#expr "=%d\n", expr)
	  dprint(x)  -> printf("x" "=%d\n", x);

   2).##: concatenate actual arguments. If a parameter in the replacement text is adja-
          cent to a ##, the parameter is replaced by the actual argument, the ## and sur-
          rounding white space are removed

	  e.g. #define paste(front, back) front ## back
          paste(name, 1)  ->  name1
  
9. conditional inclusion: include code selectively
   1).
   #if (constant integer expression: defined(xxx))
      ...
   #elif ... 
      ...
   #else
      ...
   #endif
 
   2). 
   #ifndef(#ifdef) xxx
   ... 
   #endif 


## Chapter 5. 

## Chapter 6. 

## Chapter 7. 

## Chapter 8. 
