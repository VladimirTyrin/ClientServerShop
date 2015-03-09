#include <iostream>

#include "Server.h"

using namespace std;

int main()
{
	cout << "Hello! I am a server!" << endl;
	
	Server server;
	server.start("data.txt");
	
	return 0;
}
