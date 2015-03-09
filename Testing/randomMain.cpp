#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>

#include "../Libraries/DateProcessor.h"
#include "../Libraries/GeneralMethods.h"

using namespace std;

int getRandom(int min, int max);
int getRandom(int max);

string getRandomString(int len);
string getRandomDate(); // Between 01.01.1990 and 31.12.2020

DateProcessor date_processor;

/* -------------------------------------------------- */

int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		cout << "Not enough arguments." << endl;
		cout << "Correct : ./random [record_number] [file_name]" << endl;
		return -1;
	}
	if (!checkInt(string(argv[1])))
	{
		cout << "First argument is not a number!" << endl;
		cout << "Correct : ./random [record_number] [file_name]" << endl;
		return -1;
	}
	
	int record_num = atoi(argv[1]);
	if (record_num < 0)
	{
		cout << "Negative records number!" << endl;
		cout << "Correct : ./random [record_number] [file_name]" << endl;
		return -1;
	}
	
	string fileName = argc - 2 ? string(argv[2]) : "data.txt";
	ofstream ofile;
	ofile.open(fileName.c_str());
	
	for (int i = 0; i < record_num; ++i)
	{
		ofile << "ID : " << getRandom(0, 10000) << endl;
		ofile << "Item : " << getRandomString(10) << endl;
		ofile << "Price : " << (double)getRandom(100, 10000) / 100 << endl;
		ofile << "Date : " << getRandomDate() << endl;
		if (i + 1 < record_num)
			ofile << endl;
	}
	
	ofile.close();
	return 0;
}

/* -------------------------------------------------- */

int getRandom(int min, int max)
{
	return min + (rand() % (max - min + 1));
}

/* -------------------------------------------------- */

int getRandom(int max)
{
	return getRandom(0, max);
}

/* -------------------------------------------------- */

string getRandomString(int len)
{
	string result = "";
	if (len < 0)
		throw runtime_error("Negative string length in getRandomString()");
	
	int capital;
	for (int i = 0; i < len; ++i)
	{
		capital = rand() % 2;
		if (capital)
			result += (char)((int)'A' + (rand() % ((int)'Z' - (int)'A' + 1)));
		else
			result += (char)((int)'a' + (rand() % ((int)'z' - (int)'a' + 1)));
	}
	return result;
}

/* -------------------------------------------------- */

string getRandomDate()
{
	int minutes = rand() % MINUTES_PER_HOUR;
	int hours = rand() % HOURS_PER_DAY;
	int month = 1 + (rand() % MONTHS_PER_YEAR);
	int year = getRandom(1990, 2020);
	
	int day;
	if (month == February)
		day = getRandom(1, date_processor.monthLength(February) + date_processor.isLeapYear(year));
	else
		day = getRandom(1, date_processor.monthLength(month));
	
	string result;
	
	result += hours < 10 ? "0" : "";
	result += intToString(hours);
	
	result += minutes < 10 ? "0" : "";
	result += intToString(minutes);
	
	result += day < 10 ? "0" : "";
	result += intToString(day);
	
	result += month < 10 ? "0" : "";
	result += intToString(month);
	
	result += intToString(year);

	return result;
}

