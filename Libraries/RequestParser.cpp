#include "RequestParser.h"

//#define _DEBUG_

RequestArguments * RequestParser::parseRequest(string request)
{
	_args = new RequestArguments();
	#ifdef _DEBUG_
		cout << "_separators : " << _separators.size() << endl;
		for (int i = 0; i < _separators.size(); ++i)
			cout << _separators[i] << endl;
	#endif
	
	string temp_str = insertSpaces(request, _separators);
	vector<string> words;
	vector<string> * tv = split(temp_str);
	for (unsigned int i = 0; i < tv->size(); ++i)
		words.push_back((*tv)[i]);
	delete tv;
	
	#ifdef _DEBUG_
		cout << "Request words : " << endl;
		for (int i = 0; i < words.size(); ++i)
			cout << i << "\t" << words[i] << endl;
	#endif
	
	if (words[0] != "select")
	{
		(*_args).correct = false;
		return _args;
	}
	vector<string> der_words = vector<string>(words.begin() + 1, words.end());
	
	_processSelect(der_words);
	return _args;
}

/* ---------------------------------------------------- */

void RequestParser::_processSelect(vector<string> words)
{
	#ifdef _DEBUG_
		cout << "Started _processSelect : " << endl;
		for (int i = 0; i < words.size(); ++i)
			cout << i << "\t" << words[i] << endl;
	#endif
	vector<string> der_words;
	if (!words.size())
		return;
	if (words[0] == "user")
	{
		if (words[1] != "=" || !checkInt(words[2]))
		{
			(*_args).correct = false;
			return;
		}
		
		(*_args).useId = 1;
		(*_args).ID = atoi(words[2].c_str());
		
		if (words.size() == 3)
			return;
		else
			der_words = vector<string>(words.begin() + 3, words.end());
	}
	else
	{
		(*_args).useId = 0;
		der_words = words;
	}
	
	if (der_words.size() < 2)
	{
		(*_args).correct = false;
		return;
	}
	else
	{
		if (der_words[0] != "period" || der_words[1] != "=")
		{
			(*_args).correct = false;
			return;
		}
	}
	_fillPeriod(_fixPeriodArgs(vector<string>(der_words.begin() + 2, der_words.end())));
	return;
}

/* ---------------------------------------------------- */

void RequestParser::_fillPeriod(vector<string> words)
{
	#ifdef _DEBUG_
		cout << "Entered _fillPeriod" << endl;
		cout << "der_words : " << endl;
		for (int i = 0; i < words.size(); ++i)
			cout << i << "\t" << words[i] << endl;
	#endif
	(*_args).useDate = 1;
	if (words[0] != "[" || words.size() < 3)
	{
		(*_args).correct = false;
		return;
	}
	vector<string> min_words;
	vector<string> max_words;
	
	unsigned int i = 1;
	while (words[i] != ",")
	{
		if (i == words.size() - 1 || words[i] == "]")
		{
			(*_args).correct = false;
			return;
		}
		min_words.push_back(words[i]);
		++i;
	}
	
	_fillMinTime(min_words);
	
	++i;
	while (i < words.size())
	{
		if (words[i] == "]" || i == words.size())
			break;
		max_words.push_back(words[i]);
		++i;
	}
	if (i < words.size() - 1)
	{
		(*_args).correct = false;
		return;
	}
	
	_fillMaxTime(max_words);
	return;
}

/* ---------------------------------------------------- */

void RequestParser::_fillMinTime(vector<string> words)
{
	#ifdef _DEBUG_
		cout << "Entered _fillMinTime" << endl;
		cout << "der_words : " << endl;
		for (int i = 0; i < words.size(); ++i)
			cout << i << "\t" << words[i] << endl;
	#endif
	
	string temp_date;
	string temp_time;
	char * date_beginning = (*_args).minDate + 4;;
	
	switch (words.size())
	{
		case 0:
			memcpy((*_args).minDate, MIN_DATE, DATE_LEN);
			break;
		case 1:
			temp_date = _date_processor.makeGoodDate(words[0]);
			if (temp_date == "NOTADATE")
			{
				(*_args).correct = false;
				return;
			}
			memcpy(date_beginning, temp_date.c_str(), 8);
			memcpy((*_args).minDate, "0000", 4);
			break;
		case 2:
			temp_date = _date_processor.makeGoodDate(words[0]);
			if (temp_date == "NOTADATE")
			{
				(*_args).correct = false;
				return;
			}
			memcpy(date_beginning, temp_date.c_str(), 8);
			
			temp_time = _date_processor.makeGoodTime(words[1]);
			if (temp_time == "NOTATIME")
			{
				(*_args).correct = false;
				return;
			}
			memcpy((*_args).minDate, temp_time.c_str(), 4);
			break;
		default:
			(*_args).correct = false;
			return;
	}
	return;
}

/* ---------------------------------------------------- */

void RequestParser::_fillMaxTime(vector<string> words)
{
	#ifdef _DEBUG_
		cout << "Entered _fillMaxTime" << endl;
		cout << "der_words : " << endl;
		for (int i = 0; i < words.size(); ++i)
			cout << i << "\t" << words[i] << endl;
	#endif
	
	string temp_date;
	string temp_time;
	char * date_beginning = (*_args).maxDate + 4;
	
	switch (words.size())
	{
		case 0:
			memcpy((*_args).maxDate, MAX_DATE, DATE_LEN);
			break;
		case 1:
			temp_date = _date_processor.makeGoodDate(words[0]);
			if (temp_date == "NOTADATE")
			{
				(*_args).correct = false;
				return;
			}
			memcpy(date_beginning, temp_date.c_str(), 8);
			memcpy((*_args).maxDate, "2359", 4);
			break;
		case 2:
			temp_date = _date_processor.makeGoodDate(words[0]);
			if (temp_date == "NOTADATE")
			{
				(*_args).correct = false;
				return;
			}
			memcpy(date_beginning, temp_date.c_str(), 8);
			
			temp_time = _date_processor.makeGoodTime(words[1]);
			if (temp_time == "NOTATIME")
			{
				(*_args).correct = false;
				return;
			}
			memcpy((*_args).maxDate, temp_time.c_str(), 4);
			break;
		default:
			(*_args).correct = false;
			return;
	}
	return;
}

/* ---------------------------------------------------- */
	
vector<string> RequestParser::_fixPeriodArgs(vector<string> words)
{
	vector<string> der_words;
	int words_size = words.size();
	if (words[0] != "[" && words[words_size - 1] != "]")
	{
		der_words.push_back("[");
		for (int i = 0; i < words_size; ++i)
			der_words.push_back(words[i]);
		der_words.push_back(",");
		for (int i = 0; i < words_size; ++i)
			der_words.push_back(words[i]);
		der_words.push_back("]");
	}
	else
	{
		for (int i = 0; i < words_size; ++i)
			der_words.push_back(words[i]);
	}
	return der_words;
}

