#include "DataBase.h"

using namespace std;

void DataBase::_addRecord(Purchase purchase)
{
	_dataVector.push_back(purchase);
	
	int 	idKey = purchase.user_id;
	string 	nameKey = string(purchase.date);
	
	if (_purchaseIDMap.find(idKey) == _purchaseIDMap.end())
		_purchaseIDMap[idKey] = new vector<int>();
	_purchaseIDMap[idKey]->push_back(_dataVector.size() - 1);
	
	if (_purchaseDateMap.find(nameKey) == _purchaseDateMap.end())
		_purchaseDateMap[nameKey] = new vector<int>();
	_purchaseDateMap[nameKey]->push_back(_dataVector.size() - 1);
}

/* ---------------------------------------------------- */

int DataBase::readData(const char * filename)
{
	ifstream * infile = new ifstream(filename);
	vector<Purchase> * temp_vector = _reader.readWholeFile(infile);
	int result = temp_vector->size();
	for (int i = 0; i < result; ++i)
		_addRecord((*temp_vector)[i]);
	delete infile; 
	delete temp_vector;
	return result;
}

/* ---------------------------------------------------- */

int DataBase::readData(string filename)
{
	return readData(filename.c_str());
}

/* ---------------------------------------------------- */
	
void DataBase::printIDMap()
{
	for (map<int, vector<int> *>::iterator iter = _purchaseIDMap.begin(); iter != _purchaseIDMap.end(); ++iter)
	{
		cout << (*iter).first << "\t";
		if ((*iter).second->size() == 0)
			continue;
		for (vector<int>::iterator i = (*iter).second->begin(); i != (*iter).second->end(); ++i)
			cout << *i << " ";
		cout << endl;
	}
	cout << endl;
}

/* ---------------------------------------------------- */

void DataBase::printDateMap()
{
	for (map<string, vector<int> *, DateComparator>::iterator iter = _purchaseDateMap.begin(); iter != _purchaseDateMap.end(); ++iter)
	{
		_date_processor.printDate((*iter).first.c_str());
		cout << "\t";
		if ((*iter).second->size() == 0)
			continue;
		for (vector<int>::iterator i = (*iter).second->begin(); i != (*iter).second->end(); ++i)
			cout << *i << " ";
		cout << endl;
	}
	cout << endl;
}

/* ---------------------------------------------------- */

RequestArguments * DataBase::_parseRequest(string request)
{
	return _request_parser.parseRequest(request);
}

/* ---------------------------------------------------- */

vector<Purchase> * DataBase::_selectStudents(RequestArguments * args)
{
	if (!args)
		throw runtime_error("NULL args in _selectStudents()");
	if (!args->correct)
	{
		delete args;
		return (vector<Purchase> *)NULL;			
	}
	list<int> good_id;
	list<int> good_date;
	list<int> * good_record;
	vector<Purchase> * result = new vector<Purchase>();
	if (!args->useId && !args->useDate)
	{
		for (vector<Purchase>::iterator iter = _dataVector.begin(); iter != _dataVector.end(); ++iter)
			result->push_back(*iter);
		delete args;
		return result;
	}
	
	if (args->useId)
	{
		if (_purchaseIDMap.find(args->ID) == _purchaseIDMap.end())
		{
			delete args;
			return result;
		}
		else
		{
			for (vector<int>::iterator iter = _purchaseIDMap[args->ID]->begin(); iter != _purchaseIDMap[args->ID]->end(); ++iter)
				good_id.push_back(*iter);
		}
	}
	
	if (args->useDate)
	{
		if 	(_purchaseDateMap.lower_bound(string(args->minDate)) == _purchaseDateMap.end() ||
			_purchaseDateMap.upper_bound(string(args->maxDate)) == _purchaseDateMap.begin())
		{
			delete args;
			return result;
		}
		else
		{
			for (map<string, vector<int> *, DateComparator>::iterator iter = _purchaseDateMap.lower_bound(string(args->minDate));
				iter != _purchaseDateMap.upper_bound(string(args->maxDate)); ++iter)
			{
				for (vector<int>::iterator i = (*iter).second->begin(); i != (*iter).second->end(); ++i)
				{
					good_date.push_back(*i);
				}	
			}
		}
	}
	good_record = listIntersection(good_id, good_date);
	for (list<int>::iterator iter = good_record->begin(); iter != good_record->end(); ++iter)
		result->push_back(_dataVector[*iter]);
	delete good_record;
	delete args;
	return result;
}

/* ---------------------------------------------------- */

vector<Purchase> * DataBase::processRequest(string request)
{
	return _selectStudents(_parseRequest(request));
}

/* ---------------------------------------------------- */

void DataBase::printData(ostream * file)
{
	for (vector<Purchase>::iterator iter = _dataVector.begin(); iter != _dataVector.end(); ++iter)
	{
		_printer.printPurchase(*iter, file);
	}
}


