#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

#include "Purchase.h"
#include "DateProcessor.h"
#include "Printer.h"
#include "RequestParser.h"
#include "Reader.h"

using namespace std;

class DataBase
{
private:
	vector<Purchase>	_dataVector;
	
	map<int, vector<int> *> 			_purchaseIDMap;
	map<string, vector<int> *, DateComparator>	_purchaseDateMap;
	
	Reader			_reader;
	Printer 		_printer;
	DateProcessor 		_date_processor;
	RequestParser		_request_parser;
	
	void 			_addRecord(Purchase purchase);
	RequestArguments *	_parseRequest(string request);
	vector<Purchase> *	_selectStudents(RequestArguments * args);
	
public:
	DataBase()
	{
	}
	
	DataBase(const char * filename)
	{
		readData(filename);
	}
	
	DataBase(string filename)
	{
		readData(filename);
	}
	
	~DataBase()
	{
		while (_dataVector.size())
		{
			delete [] (*(_dataVector.begin())).item;
			_dataVector.erase(_dataVector.begin());
		}
		for (map<int, vector<int> *>::iterator iter = _purchaseIDMap.begin(); iter != _purchaseIDMap.end(); ++iter)
			delete (*iter).second;
		for (map<string, vector<int> *, DateComparator>::iterator iter = _purchaseDateMap.begin(); iter != _purchaseDateMap.end(); ++iter)
			delete (*iter).second;
			
	}
	
	int 	count()
	{
		return _dataVector.size();
	}
	
	int 	readData(const char * filename);
	int 	readData(string filename);
	
	void 	printData(ostream * file = &cout);
	void 	printIDMap();
	void	printDateMap();
	
	vector<Purchase> * 	processRequest(string request);
};

#endif
