#include "DateProcessor.h"

using namespace std;

/* ----------------------------------------------- */

bool DateProcessor::checkDate(const char * const date)
{
	if (strlen(date) != DATE_LEN)
		return false;
	for (int i = 0; i < DATE_LEN; ++i)
	{
		if (date[i] < '0' || date[i] > '9')
			return false;
	}	
	
	int hours = (date[0] - (int)'0') * 10 + (date[1] - (int)'0');
	if (hours >= HOURS_PER_DAY)
		return false;
		
	int minutes = (date[2] - (int)'0') * 10 + (date[3] - (int)'0');
	if (minutes >= MINUTES_PER_HOUR)
		return false;
		
	int year = (date[8] - (int)'0') * 10 + (date[9] - (int)'0');
	year *= 100;
	year += (date[10] - (int)'0') * 10 + (date[11] - (int)'0');
	
	int month = (date[6] - (int)'0') * 10 + (date[7] - (int)'0');
	if (month > MONTHS_PER_YEAR)
		return false;
	
	int day = (date[4] - (int)'0') * 10 + (date[5] - (int)'0');
	if (day > monthLength(month) + ((month == February ? 1 : 0) * isLeapYear(year)))
		return false;
	return true;
}

/* ----------------------------------------------- */

int DateProcessor::compareDates(const char * const date_1, const char * const date_2)
{
	int priority[] = {8, 9, 10, 11, 6, 7, 4, 5, 0, 1, 2, 3};
	for (int i = 0; i < DATE_LEN; ++i)
	{
		if (date_1[priority[i]] > date_2[priority[i]])
			return 1;
		if (date_1[priority[i]] < date_2[priority[i]])
			return -1;
	}
	return 0;
}

/* ----------------------------------------------- */

int DateProcessor::monthLength(int month)
{
	switch (month)
	{
		case 1: 	return 31;
		case 2: 	return 28; // Leap years will be processed in another place
		case 3: 	return 31;
		case 4: 	return 30;
		case 5: 	return 31;
		case 6: 	return 30;
		case 7: 	return 31;
		case 8: 	return 31;
		case 9: 	return 30;
		case 10: 	return 31;
		case 11: 	return 30;
		case 12: 	return 31;
		
		default:
			throw runtime_error("Wrong month number in monthLength()");
	}
}

/* ----------------------------------------------- */

void DateProcessor::printDate(const char * const date, ostream * const stream)
{
	if (strlen(date) != DATE_LEN)
	{
		cout << "Bad date : " << strlen(date) << " " << date << endl;
 		throw runtime_error("Wrong date format in printDate()");
	}
	(*stream) << date[4] << date[5] << "." << date[6] << date[7] << ".";
	(*stream) << date[8] << date[9] << date[10] << date[11] << " ";
	(*stream) << date[0] << date[1] << ":" << date[2] << date[3];
}

/* ----------------------------------------------- */

string DateProcessor::makeGoodDate(string date) // NOTADATE for error
{
	string 		result;
	string 		part;
	int 		symbols_before_dot = 0;
	unsigned int 	position = 0;
	
	for (int i = 0; i < 2; ++i)
	{
		while (position < date.size())
		{
			if (date[position] == '.')
			{
				++position;
				break;
			}
			else if (date[position] >= '0' && date[position] <= '9')
			{
				part += date[position];
				++symbols_before_dot;
				++position;
			}
			else
				return string("NOTADATE");
		}
		switch (symbols_before_dot)
		{
			case 0:
				return string("NOTADATE");
			case 1:
				result += "0";
			case 2:
				result += part;
				break;
			default:
				return string("NOTADATE");
		}
		symbols_before_dot = 0;
		part = "";
	}
	
	while (position < date.size())
	{
		if (date[position] >= '0' && date[position] <= '9')
		{
			part += date[position];
			++symbols_before_dot;
			++position;
		}
		else
			return string("NOTADATE");
	}
	switch (symbols_before_dot)
	{
		case 0:
			return string("NOTADATE");
		case 1:
			result += "0";
		case 2:
			result += "0";
		case 3:
			result += "0";
		case 4:
			result += part;
			break;
		default:
			return string("NOTADATE");
	}
	
	if (!checkDate((string("0000") + result).c_str()))
		return string("NOTADATE");
	return result;
}

/* ----------------------------------------------- */

string DateProcessor::makeGoodTime(string date) // NOTATIME for error
{
	string 		result; 
	string 		part;
	int 		symbols_before_dot = 0;
	unsigned int 	position = 0;
	
	while (position < date.size())
	{
		if (date[position] == ':')
		{
			++position;
			break;
		}
		else if (date[position] >= '0' && date[position] <= '9')
		{
			part += date[position];
			++symbols_before_dot;
			++position;
		}
		else
			return string("NOTATIME");
	}
	switch (symbols_before_dot)
	{
		case 0:
			return string("NOTATIME");
		case 1:
			result += "0";
		case 2:
			result += part;
			break;
		default:
			return string("NOTATIME");
	}
	symbols_before_dot = 0;
	part = "";
	
	while (position < date.size())
	{
		if (date[position] >= '0' && date[position] <= '9')
		{
			part += date[position];
			++symbols_before_dot;
			++position;
		}
		else
			return string("NOTATIME");
	}
	switch (symbols_before_dot)
	{
		case 0:
			return string("NOTATIME");
		case 1:
			result += "0";
		case 2:
			result += part;
			break;
		default:
			return string("NOTATIME");
	}
	if (!checkDate((result + string("01010000")).c_str()))
		return string("NOTATIME");
	return result;
}

