/*
Write the program expr, which evaluates a reverse Polish
expression from the command line, where each operator or operand is a separate
argument. For example,

expr 2 3 4 + *
evaluates 2 x (3+4).

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE	100

int stack[MAX_SIZE], sp = -1;

int pop()
{
	if(sp < 0)
	{
		fprintf(stderr, "illegal expr\n");
		exit(1);
	}
	return stack[sp--];	
}

void push(int x)
{
	if(sp == MAX_SIZE-1)
	{
		fprintf(stderr, "overflow\n");
		exit(1);
	}
	stack[++sp] = x;
}

int expr(char *argv[])
{
	char *buf, *p;
	int op1, op2, i = 1;
	
	while(argv[i] != NULL)
	{
		p = argv[i];
		if(strcmp(p, "+") == 0)
		{
			op2 = pop();
			op1 = pop();
			push(op1+op2);									
		}	
		else if(strcmp(p, "-") == 0)
                {
                        op2 = pop();
                        op1 = pop();
                        push(op1-op2);
                }	
		else if(strcmp(p, "*") == 0)
                {
                        op2 = pop();
                        op1 = pop();
                        push(op1*op2);
                }
		else if(strcmp(p, "/") == 0)
                {
                        op2 = pop();
                        op1 = pop();
			if(op2 == 0)
			{
				fprintf(stderr, "divide by zero\n");
				exit(1);
			}
                        push(op1/op2);
                }
		else
		{
			op1 = (int)strtol(p, &buf, 10);
			if(buf[0] != '\0')
			{
				fprintf(stderr, "illegal expr\n");
				exit(1);
			}
			push(op1);
		}
		i++;
	}	
	return pop();					
}

int main(int argc, char *argv[])
{
	printf("%d\n", expr(argv));
	return 0;		
}
