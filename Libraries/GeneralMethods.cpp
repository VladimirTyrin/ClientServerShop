#include "GeneralMethods.h"

//#define _DEBUG_
#ifdef _DEBUG_
	#include <iostream>
#endif

vector<string> * split(string str)
{
	vector<string> * result = new vector<string>();
	result->push_back("");
	int k = 0;
	bool newWord;
	for (unsigned int i = 0; i < str.size(); ++i)
	{
		newWord = false;
		while (str[i] == ' ')
		{
			++i;
			newWord = true;
			if (i >= str.size())
				break;
		}
		if (newWord && i < str.size())
		{
			result->push_back("");
			++k;
		}
		(*result)[k] += str[i];
	}
	return result;
}

/* ------------------------------------------------ */

bool checkInt(string str)
{
	unsigned int k = 0;
	if (str[0] == '-')
	{
		if (str.size() > 1)
			++k;
		else
			return false;
	}
	while (k < str.size())
	{
		if (str[k] > '9' || str[k] < '0')
			return false;
		++k;
	}
	return true;
}

/* ------------------------------------------------ */

bool checkDouble(string str)
{
	unsigned int k = 0;
	int dot_seen = 0;
	if (str[0] == '-')
	{
		if (str.size() > 1)
			++k;
		else
			return false;
	}
	while (k < str.size())
	{
		if (str[k] == '.')
		{
			if (dot_seen || k == str.size() - 1)
				return false;
			else
			{
				++dot_seen;
				++k;
				continue;
			}
		}
		if (str[k] > '9' || str[k] < '0')
			return 0;
		++k;
	}
	return true;
}

/* ------------------------------------------------ */

string intToString(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}

/* ------------------------------------------------ */

string insertSpaces(string str, vector<char> separators)
{
	#ifdef _DEBUG_
		cout << "Entered insert Spaces : " << separators.size() << endl;
		for (int i = 0; i < separators.size(); ++i)
			cout << separators[i] << endl;
	#endif
	if (separators.size() == 0)
		return string(str);
	for (unsigned int i = 0; i < separators.size(); ++i)
	{
		if (separators[i] == ' ')
			throw runtime_error("Whitespace cannot be a separator in insertSpaces()");
	}
	
	string result = str;
	unsigned int k = 0;
	while (k < result.size())
	{
		for (unsigned int i = 0; i < separators.size(); ++i)
		{
			if (result[k] == separators[i])
			{
				result.insert(k, 1, ' ');
				++k;
				if (k + 1 < result.size())
				{
					result.insert(k + 1, 1, ' ');
					++k;
				}
				break;
			}
		}
		++k;
	}
	#ifdef _DEBUG_
		cout << "Finished insert Spaces : " << separators.size() << endl;
		cout << "Result : " << result << endl;
	#endif
	return result;
}

/* ------------------------------------------------ */

list<int> * listIntersection(list<int> firstList, list<int> secondList)
{
	firstList.sort();
	firstList.unique();
	secondList.sort();
	secondList.unique();
	
	list<int> * result = new list<int>();
	if (!firstList.size())
		return new list<int>(secondList);
	if (!secondList.size())
		return new list<int>(firstList);
	
	for (list<int>::iterator iter = secondList.begin(); iter != secondList.end(); ++iter)
	{
		firstList.push_back(*iter);
	}
	firstList.sort();
	int temp = *(firstList.begin());
	list<int>::iterator i = firstList.begin();
	++i;
	
	while (i != firstList.end())
	{
		if (temp == *i)
			result->push_back(temp);
		temp = *i;
		++i;
	}
	return result;
}

