#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <vector>

#include "Purchase.h"
#include "DateProcessor.h"
#include "RequestArguments.h"

using namespace std;

class Printer
{
private:
	DateProcessor _date_processor;
public:
	Printer()
	{
		
	}

	void printPurchase(Purchase purchase, ostream * const stream = &cout);
	void printPurchaseVector(vector<Purchase> * const purchase_vector, ostream * const stream = &cout);
	
	void printRequestArguments(RequestArguments args, ostream * const stream = &cout);
};

#endif
