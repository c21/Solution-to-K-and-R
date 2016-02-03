#include <limits.h>
#include <float.h>
#include <stdio.h>

main()
{
	printf("signed char min: %d\n", SCHAR_MIN);
	printf("signed char max: %d\n", SCHAR_MAX);
	printf("unsigned char max: %d\n\n", UCHAR_MAX);			

	printf("signed short min: %d\n", SHRT_MIN);
        printf("signed short max: %d\n", SHRT_MAX);
        printf("unsigned short max: %d\n\n", USHRT_MAX);

	printf("signed int min: %d\n", INT_MIN);
        printf("signed int max: %d\n", INT_MAX);
        printf("unsigned int max: %u\n\n", UINT_MAX);

	printf("signed long min: %ld\n", LONG_MIN);
        printf("signed long max: %ld\n", LONG_MAX);
        printf("unsigned long max: %lu\n\n", ULONG_MAX);	

	printf("float min: %g\n", FLT_MIN);
        printf("float max: %g\n\n", FLT_MAX);
	
	printf("double min: %g\n", DBL_MIN);
        printf("double max: %g\n\n", DBL_MAX);
	
	printf("long double min: %Lg\n", LDBL_MIN);
        printf("long double max: %Lg\n", LDBL_MAX);
}

