#include <iostream>

#include "Client.h"

using namespace std;

int main(int argc, char ** argv)
{
 	cout << "Hello! I am a HTML client!" << endl;
	Client * client;
	switch (argc)
	{
		case 2:
			try
			{
				client = new Client();
				client->startHTML(NULL, argv[1]);
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
				client = new Client();
				client->startHTML(argv[1], argv[2]);
				delete client;
			}
			catch (runtime_error err)
			{
				cout << "Error : " << err.what() << endl;
			}
			break;
		case 5:
			try
			{
				client = new Client(argv[1], atoi(argv[2]));
				client->startHTML(argv[3], argv[4]);
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
}

