
/*static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
*/
#include <stdlib.h>

static char* daytab[2];

void initialization()
{
	int i, m;
	for(i = 0; i <= 1; i++)
	{
		daytab[i] = (char*)malloc(sizeof(char)*13);
		for(m = 0; m <= 12; m++)
		{
			switch(m)
			{
				case 0: daytab[i][m] = 0; break;
				case 1: 
				case 3: 
				case 5:	
				case 7:
				case 8:
				case 10:
				case 12: daytab[i][m] = 31; break;
				case 4:
				case 6:
				case 9:
				case 11: daytab[i][m] = 30; break;
				case 2: daytab[i][m] = i ? 29:28; break;
			}
		}
	}	
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	if(year < 0)
		return -1;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	if(month < 1 || month > 12 || day < 1 || day > daytab[leap][momth])
		return -1;

	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap, mday;
	if(year < 0)
	{
		*pmonth = -1;
		*pday = -1;
		return;
	}

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	mday = (leap ? 366 : 365);
	if(yearday < 1 || yearday > mday)	
	{
		*pmonth = -1;
                *pday = -1;
                return;
	}
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

