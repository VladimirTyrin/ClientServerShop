#ifndef GENERAL_METHODS_H
#define GENERAL_METHODS_H

#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

vector<string> * split(string str);

bool checkInt(string str);
bool checkDouble(string str);

string intToString(int num);
string insertSpaces(string str, vector<char> separators);

list<int> * listIntersection(list<int> firstList, list<int> secondList);

#endif
