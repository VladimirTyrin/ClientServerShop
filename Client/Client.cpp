#include "Client.h"

//#define _DEBUG_

Client::Client(const char * address, int _port)
{
	_hp = gethostbyname(address);
	_port = _port;
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
	{
		throw runtime_error("Cannot create socket!");
	}
	_serv_addr.sin_family = AF_INET;
    	bcopy(_hp->h_addr, &_serv_addr.sin_addr, _hp->h_length); 
    	_serv_addr.sin_port = htons(_port);
    	cout << "Server IP : " << inet_ntoa(_serv_addr.sin_addr) << endl;
	cout << "Server port : " << _serv_addr.sin_port << endl << endl;
    	int succeeded = connect(_socket, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr));
    	if (succeeded == 0)
    	{
    		cout << "Connection established" << endl;
    	}
    	else
    	{
    		throw runtime_error("Cannot connect!");
    	}	
}

/* -------------------------------------------- */

int Client::start(char * request)
{	
	char * 	buff = new char[BUFF_SIZE];
	int 	records;
	int	code_len;
	
	if (request)
	{
		memcpy(buff, request, strlen(request));
		buff[strlen(request)] = '\0';
	}
	else
	{
		cout << "Input request : ";
		scanf("%s", buff);
	}
	cout << "Request : " << buff << endl;
	
	int len = strlen(buff);
	write(_socket, &len, sizeof(int));
	write(_socket, buff, strlen(buff));
	
	int request_type;
	read(_socket, &request_type, sizeof(int));
	
	vector<Purchase> purchases;
	Printer printer;
	
	switch (request_type)
	{
		case INCORRECT:
			cout << "Request is not correct!" << endl;
			break;
		case STOP_SERVER:
			cout << "Server stopped." << endl;
			break;
		case CORRECT:
			cout << "Request is correct. Start recieving data..." << endl;
			read(_socket, &records, sizeof(int));
			if (records < 0)
			{
				cout << "Error : negative number of records!" << endl;
				break;
			}
			for (int i = 0; i < records; ++i)
			{
				read(_socket, &code_len, sizeof(int));
				read(_socket, buff, code_len);
				
				#ifdef _DEBUG_
					cout << "Code length : " << code_len << endl;
					cout << "Code : ";
					for (int j = 0; j < code_len; ++j)
						cout << buff[j];
					cout << endl;
					cin.get();
				#endif
				
				purchases.push_back(_coder.getPurchaseByCode(buff));
				
				code_len = 0;
			}
			printer.printPurchaseVector(&purchases);
			
			for (unsigned int i = 0; i < purchases.size(); ++i)
				delete [] purchases[i].item;
			
			break;
		default:
			cout << "Server error : unknown request type." << endl;
			break;
	}
	
	close(_socket);
	delete [] buff;
	return request_type;
}

/* -------------------------------------------- */

int Client::startHTML(char * request, char * filename)
{
	char * 	buff = new char[BUFF_SIZE];
	int 	records;
	int	code_len;
	
	if (request)
	{
		memcpy(buff, request, strlen(request));
		buff[strlen(request)] = '\0';
	}
	else
	{
		cout << "Input request : ";
		scanf("%s", buff);
	}
	cout << "Request : " << buff << endl;
	
	int len = strlen(buff);
	write(_socket, &len, sizeof(int));
	write(_socket, buff, strlen(buff));
	
	int request_type;
	read(_socket, &request_type, sizeof(int));
	
	vector<Purchase> purchases;
	HTMLGenerator * html_generator;
	
	switch (request_type)
	{
		case INCORRECT:
			cout << "Request is not correct!" << endl;
			break;
		case STOP_SERVER:
			cout << "Server stopped." << endl;
			break;
		case CORRECT:
			cout << "Request is correct. Start recieving data..." << endl;
			read(_socket, &records, sizeof(int));
			if (records < 0)
			{
				cout << "Error : negative number of records!" << endl;
				break;
			}
			for (int i = 0; i < records; ++i)
			{
				read(_socket, &code_len, sizeof(int));
				read(_socket, buff, code_len);
				
				#ifdef _DEBUG_
					cout << "Code length : " << code_len << endl;
					cout << "Code : ";
					for (int j = 0; j < code_len; ++j)
						cout << buff[j];
					cout << endl;
					cin.get();
				#endif
				
				purchases.push_back(_coder.getPurchaseByCode(buff));
				
				code_len = 0;
			}
			
			html_generator = new HTMLGenerator(filename);
			html_generator->makeHeader();
			html_generator->printRequest(string(request));
			html_generator->printPurchaseVector(&purchases);
			html_generator->makeFooter();
			delete html_generator;
			
			for (unsigned int i = 0; i < purchases.size(); ++i)
				delete [] purchases[i].item;
			
			break;
		default:
			cout << "Server error : unknown request type." << endl;
			break;
	}
	
	close(_socket);
	delete [] buff;
	return request_type;
}

