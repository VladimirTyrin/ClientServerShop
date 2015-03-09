#ifndef READER_H
#define READER_H

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>

#include "Purchase.h"
#include "DateProcessor.h"
#include "GeneralMethods.h"

using namespace std;

class Reader
{
private:
	DateProcessor 	_date_processor;
public:
	Reader()
	{
	
	}
	
	Purchase 		readPurchase(ifstream * const file);
	vector<Purchase> * 	readWholeFile(ifstream * const file);
};

#endif
