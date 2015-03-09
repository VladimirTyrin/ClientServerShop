#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>

#include "RequestArguments.h"
#include "GeneralMethods.h"
#include "DateProcessor.h"

using namespace std;

// Select user = X period = [min, max]
class RequestParser
{
private: 
	string 			_request_str;
	vector<char>		_separators;
	RequestArguments *	_args;
	DateProcessor		_date_processor;
	
	void 			_processSelect(vector<string> words);
	void			_fillPeriod(vector<string> words);
	
	void 			_fillMinTime(vector<string> words);
	void 			_fillMaxTime(vector<string> words);
	
	vector<string> 		_fixPeriodArgs(vector<string> words);
public:
	RequestParser()
	{
		_separators.push_back('[');
		_separators.push_back(']');
		_separators.push_back('=');
		_separators.push_back(',');
	}
	
	~RequestParser()
	{
	}
	
	RequestArguments * 	parseRequest(string request);
};

#endif
