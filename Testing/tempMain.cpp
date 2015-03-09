#include <iostream>

#include "../Libraries/MainLib.h"

using namespace std;

int main()
{
	DateProcessor date_processor;	
	DataBase database("data.txt");
	database.printIDMap();
	database.printDateMap();
	
	ifstream 	timefile("times.txt");
	
	vector<string> *words;
	while (!timefile.eof())
	{
		string line;
		std::getline(timefile, line);
		if (line.size() == 0)
			break;
		words = split(line);
		cout << date_processor.makeGoodDate((*words)[0]) << " ";
		cout << date_processor.makeGoodTime((*words)[1]) << endl;
		delete words;
	}
	
	
	Printer 		printer;
	ifstream 		infile("input.txt");
	while (!infile.eof())
	{
		string line;
		RequestParser parser;
		std::getline(infile, line);
		if (!line.size())
			break;
		HTMLGenerator generator("test.html");
		generator.makeHeader();
		cout << endl << "Request : " << line << endl;
		vector<Purchase> * temp_vec = database.processRequest(line);
		generator.printRequest(line);
		generator.printPurchaseVector(temp_vec);
		for (vector<Purchase>::iterator iter = temp_vec->begin(); iter != temp_vec->end(); ++iter)
		{
			printer.printPurchase(*iter);
		}
		generator.makeFooter();
		delete temp_vec;
	}	
	return 0;
}
