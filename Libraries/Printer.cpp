#include "Printer.h"

//#define _DEBUG_

using namespace std;

void Printer::printPurchase(Purchase purchase, ostream * const stream)
{
	(*stream) << "ID :\t" << purchase.user_id << endl;
	(*stream) << "Item :\t" << purchase.item << endl;
	(*stream) << "Price :\t" << purchase.price << endl;
	(*stream) << "Date :\t";
	_date_processor.printDate(purchase.date, stream);
	(*stream) << endl << endl;
}

/* ------------------------------------------------------------ */

void Printer::printPurchaseVector(vector<Purchase> * const purchase_vector, ostream * const stream)
{
	for (vector<Purchase>::const_iterator iter = purchase_vector->begin(); iter != purchase_vector->end(); ++iter)
		this->printPurchase(*iter, stream);
	(*stream) << endl;
}

/* ------------------------------------------------------------ */

void Printer::printRequestArguments(RequestArguments args, ostream * const stream)
{
	(*stream) << "Type : " << (args.correct ? "Correct" : "Incorrect") << endl;
	(*stream) << "Use id : " << args.useId << endl;
	(*stream) << "ID : " << args.ID << endl;
	(*stream) << "Use date : " << args.useDate << endl;
	
	#ifdef _DEBUG_	
		(*stream) << "Min date unformatted : " << args.minDate << endl;
	#endif
	(*stream) << "Min date : ";
	_date_processor.printDate(args.minDate, stream);
	
	#ifdef _DEBUG_	
		(*stream) << endl << "Max date unformatted : " << args.maxDate;
	#endif
	(*stream) << endl << "Max date : ";
	_date_processor.printDate(args.maxDate, stream);
	(*stream) << endl;
}

