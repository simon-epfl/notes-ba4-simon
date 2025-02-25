#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

const double g = 9.81;
const int PI = 3.14;

int IsLeapYear(int y);

int main()
{

    time_t t = time(NULL);
    struct tm *ta = localtime(&t);
    printf("%d", ta->tm_year);

    int days = 42; // 31 décembre 2008; comes from the hardware in real
    int year = 1980;  // 1980, Microsoft epoch
    while (days > 365)
    {
        if (IsLeapYear(year))
        { // 2008 is a leap year
            if (days > 366)
            {
                year += 1;
            }
            days -= 366;
        }
        else
        {
            days -= 365;
            year += 1;
        }
    }

    printf("%d", year);
    printf("%d", days);
}

int IsLeapYear(int y) {
    return (0 == y % 4) && (0 != y % 100) || (0 == y % 400);
}

int DaysForMonth(int year, int month) {
    switch (month) {
        case 2:
            return IsLeapYear(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}