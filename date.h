#ifndef DATE_H
#define DATE_H

#include <stdio.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

static inline int compareDates(Date d1, Date d2) {
    if (d1.year != d2.year) return (d1.year < d2.year) ? -1 : 1;
    if (d1.month != d2.month) return (d1.month < d2.month) ? -1 : 1;
    if (d1.day != d2.day) return (d1.day < d2.day) ? -1 : 1;
    return 0;
}

static inline int daysBetween(Date from, Date to) {
    long totalDaysFrom = from.year * 365 + from.month * 30 + from.day;
    long totalDaysTo = to.year * 365 + to.month * 30 + to.day;
    return (int)(totalDaysTo - totalDaysFrom);
}

static inline void printDate(Date d) {
    printf("%02d/%02d/%04d", d.day, d.month, d.year);
}

#endif