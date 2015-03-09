#include "Reader.h"

//#define _DEBUG_

using namespace std;

Purchase Reader::readPurchase(ifstream * file)
{
	Purchase result;
	
	vector<string> * substrings;
	string line;
	
	if (file->eof())
		throw runtime_error("Unexpected end of file in readPurchase()");

	getline(*file, line);
	if (!(line.size()))
		throw runtime_error("Unexpected end of file in readPurchase() - empty line");		
	substrings = split(line);

	#ifdef _DEBUG_
		cout << "Substrings in ID line : " << endl;
		for (int i = 0; i < substrings->size(); ++i)
			cout << i << "\t " << (*substrings)[i] << endl;
	#endif 
	if (substrings->size() != 3)
		throw runtime_error("Wrong ID line format in readPurcase");
	if ((*substrings)[0] != "ID" || (*substrings)[1] != ":" || !checkInt((*substrings)[2]))
		throw runtime_error("Wrong ID line format in readPurcase");

	result.user_id = atoi((*substrings)[2].c_str());
	substrings->clear();
	delete substrings;

	getline(*file, line);			
	substrings = split(line);
	
	#ifdef _DEBUG_
		cout << "Substrings in Item line : " << endl;
		for (int i = 0; i < substrings->size(); ++i)
			cout << i << "\t " << (*substrings)[i] << endl;
	#endif 
	if (substrings->size() != 3)
		throw runtime_error("Wrong Item line format in readPurcase");
	if ((*substrings)[0] != "Item" || (*substrings)[1] != ":")
		throw runtime_error("Wrong Item line format in readPurcase");

	int item_len = (*substrings)[2].size();
	result.item = new char[item_len + 1];
	memcpy(result.item, (*substrings)[2].c_str(), item_len);
	result.item[item_len] = '\0';
	substrings->clear();
	delete substrings;
	
	getline(*file, line);			
	substrings = split(line);
	#ifdef _DEBUG_
		cout << "Substrings in Price line : " << endl;
		for (int i = 0; i < substrings->size(); ++i)
			cout << i << "\t " << (*substrings)[i] << endl;
	#endif 
	if (substrings->size() != 3)
		throw runtime_error("Wrong Price line format in readPurcase");	
	if ((*substrings)[0] != "Price" || (*substrings)[1] != ":" || !checkDouble((*substrings)[2]))
		throw runtime_error("Wrong Price line format in readPurcase");

	result.price = atof((*substrings)[2].c_str());
	substrings->clear();
	delete substrings;
	
	getline(*file, line);			
	substrings = split(line);
	#ifdef _DEBUG_
		cout << "Substrings in Size line : " << endl;
		for (int i = 0; i < substrings->size(); ++i)
			cout << i << "\t " << (*substrings)[i] << endl;
	#endif 
	if (substrings->size() != 3)
		throw runtime_error("Wrond Size line format in readPurcase");
	if ((*substrings)[0] != "Date" || (*substrings)[1] != ":" || (*substrings)[2].size() != DATE_LEN || !_date_processor.checkDate((*substrings)[2].c_str()))
		throw runtime_error("Wrong Date line format in readPurcase");

	memcpy(result.date, (*substrings)[2].c_str(), DATE_LEN);
	result.date[DATE_LEN] = '\0';
	substrings->clear();
	delete substrings;
	
	return result;
}

/* ------------------------------------------------------ */

vector<Purchase> * Reader::readWholeFile(ifstream * const file)
{
	vector<Purchase> * result = new vector<Purchase>();
	
	string line;
	while (!file->eof())
	{
		result->push_back(this->readPurchase(file));
		std::getline(*file, line);
		if (file->eof())
			break;
	}
	return result;
}
