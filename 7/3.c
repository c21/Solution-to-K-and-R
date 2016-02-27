#include <stdarg.h>
#include <stdio.h>

/* minprintf: minimal printf with variable argument list */

void minprintf(char *fmt, ...)
{
    va_list ap; 
    char *p, *sval, cval;
    int ival, count = 0, *ip;
    double dval;
    void *pval;
    va_start(ap, fmt); 
    for (p = fmt; *p; p++) 
    {
        if (*p != '%')
        {
            putchar(*p);
            count++;
            continue;
        }
        ++p;
        char cmd[3];
        cmd[0] = '%', cmd[1] = *p, cmd[2] = '\0';
        switch (*p) 
        {
                
            case 'd': 
            case 'i':
                ival = va_arg(ap, int);
                count += printf(cmd, ival);
                break;
            case 'u':
            case 'o':
            case 'x':
            case 'X': 
                ival = va_arg(ap, unsigned int);
                count += printf(cmd, ival);
                break;
            case 'f':
            case 'F':
            case 'e':
            case 'E':
            case 'g':
            case 'G':
            case 'a':
            case 'A':
                dval = va_arg(ap, double);
                count += printf(cmd, dval);
                break;
            case 's':
                for(sval = va_arg(ap, char *); *sval; sval++)
                {
                    putchar(*sval);
                    count++;
                }
                break;
            case 'c':
                cval = va_arg(ap, int);
                count += printf(cmd, cval);
                break;
            case 'p':
                pval = va_arg(ap, void *);
                count += printf(cmd, pval);
                break;  
            case 'n':
                ip = va_arg(ap, int *);
                *ip = count;
                break;
            case '%':
                count += printf("%");
                break;              
            default:
                putchar(*p);
                count++;
                break;
        }
    }
    va_end(ap); 
}

int main()
{
    minprintf("123%d %f %s\n", 1, 2.4, "123");
    int x;
    minprintf("%i%f %n", 2,123.0, &x);
    minprintf("x:%d\n", x);
    return 0;
}
