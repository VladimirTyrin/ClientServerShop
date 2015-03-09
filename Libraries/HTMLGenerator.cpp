#include "HTMLGenerator.h"

void HTMLGenerator::_printPurchase(Purchase purchase)
{
	++_numberOfRecords;
	_file << "<p>" << endl;
	_file << "\tRecord #" << _numberOfRecords << "<br>" << endl;
	_file << "<pre>" << endl;
	_file << "\t\tID :\t" << purchase.user_id << "<br>" << endl;
	_file << "\t\tItem :\t" << purchase.item << "<br>" << endl;
	_file << "\t\tPrice :\t" << purchase.price << "<br>" << endl;
	_file << "\t\tDate :\t";
	_date_processor.printDate(purchase.date, &_file);
	_file << "<br>" << endl; 
	_file << "</pre>" << endl;
	_file << "</p>" << endl;
	_totalPrice += purchase.price;
}

/* -------------------------------------------------- */

void HTMLGenerator::makeHeader()
{
	_file << "<!DOCTYPE html>" << endl;
	_file << "<html>" << endl;
	_file << "<body>" << endl;
	_file << "<h2>HTML document with selected purchases</h2>" << endl;
}

/* -------------------------------------------------- */

void HTMLGenerator::printRequest(string request)
{
	_file << "<h3>Request : " << request << "</h3>" << endl;
}

/* -------------------------------------------------- */

void HTMLGenerator::printPurchaseVector(vector<Purchase> * vec)
{
	if (!vec)
		throw runtime_error("Null pointer in HTMLGenerator::printPurchaseVector");
	for (vector<Purchase>::iterator iter = vec->begin(); iter != vec->end(); ++iter)
		_printPurchase(*iter);
}

/* -------------------------------------------------- */

void HTMLGenerator::makeFooter()
{
	time_t seconds = time(NULL);
	tm * timeinfo = localtime(&seconds);

	_file << "<h3>Total records : " << _numberOfRecords << "</h3>" << endl;
	_file << "<h3>Total price : " << _totalPrice << "</h3>" << endl;
	_file << "<h3>Document generated automatically, finished at : ";
	_file << asctime(timeinfo) << "</h3>" << endl;
	_file << "</body>" << endl;
	_file << "</html>" << endl;
}

