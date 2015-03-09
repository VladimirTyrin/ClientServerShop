#include <iostream>

#include "Client.h"

using namespace std;

int main(int argc, char ** argv)
{	
	Client * client;
	switch (argc)
	{
		case 1:
			try
			{
				client = new Client();
				client->start(NULL);
				delete client;
			}
			catch (runtime_error err)
			{
				cout << "Error : " << err.what() << endl;
			}
			break;
		case 2:
			try
			{
				client = new Client();
				client->start(argv[1]);
				delete client;
			}
			catch (runtime_error err)
			{
				cout << "Error : " << err.what() << endl;
			}
			break;
		case 3:
			try
			{
				client = new Client(argv[1], atoi(argv[2]));
				client->start(argv[3]);
				delete client;
			}
			catch (runtime_error err)
			{
				cout << "Error : " << err.what() << endl;
			}
			break;
		default:
			cout << "Wrong arguments!" << endl;
			break;
	}
	return 0;
}
