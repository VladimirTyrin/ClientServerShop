#ifndef HTML_GENERATOR_H
#define HTML_GENERATOR_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Purchase.h"
#include "DateProcessor.h"

using namespace std;

class HTMLGenerator
{
private:
	ofstream 	_file;
	double		_totalPrice;
	int		_numberOfRecords;
	DateProcessor	_date_processor;
	
	void 		_printPurchase(Purchase purchase);
public:
	HTMLGenerator(const char * filename)
	{
		_totalPrice = 0;
		_numberOfRecords = 0;
		_file.open(filename);
	}
	HTMLGenerator(string filename)
	{
		_totalPrice = 0;
		_numberOfRecords = 0;
		_file.open(filename.c_str());
	}
	HTMLGenerator()
	{
		_file.close();
	}
	
	void makeHeader();
	void printRequest(string request);
	void printPurchaseVector(vector<Purchase> * vec);
	void makeFooter();
};

#endif
