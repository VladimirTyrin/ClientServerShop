#ifndef DATE_PROCESSOR_H
#define DATE_PROCESSOR_H

#include <iostream>
#include <stdexcept>
#include <cstring>

#include "Purchase.h"

#define MINUTES_PER_HOUR 	60
#define HOURS_PER_DAY		24
#define	MONTHS_PER_YEAR		12

using namespace std;

enum Months
{
	Zero = 		0,
	January = 	1,
	February = 	2,
	March =		3,
	April = 	4,
	May = 		5,
	June = 		6, 
	July = 		7,
	August = 	8,
	September = 	9,
	October	= 	10,
	November = 	11,
	December = 	12
};

class DateProcessor
{
public:
	int 	isLeapYear(int year)
	{
		return ((year % 100) & !(year % 400)) ? 1 : 0;
	}

	bool 	checkDate(const char * const date);
	int	compareDates(const char * const date_1, const char * const date_2);
	
	int 	monthLength(int month);
	
	void 	printDate(const char * const date, ostream * const stream = &cout);
	
	string	makeGoodDate(string date);
	string 	makeGoodTime(string time);
};

struct DateComparator
{
	bool operator() (string date_1, string date_2) const
	{
		DateProcessor date_processor;
		bool result = (date_processor.compareDates(date_1.c_str(), date_2.c_str()) < 0);
		return result;
	}
};

#endif
