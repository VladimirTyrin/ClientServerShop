#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cstring>

#include "../Libraries/MainLib.h"

using namespace std;

class Server
{
private:
	DataBase		_dataBase;
	Printer			_printer;
	Coder			_coder;

	vector<int> 		_socketVector;
	vector<sockaddr_in>	_addrinfoVector;
	ostream * 		_logFile;
	filebuf 		_fb;
	
	int			_basePort;
	int			_maxSocketNumber;
	
	int 			_clientsNum;
	int 			_clientsSuccessNum;
	int			_requestsNum;
	int			_requestsSuccessNum;

	void 			_initServer(int port);	
	void 			_printCurrentTime();
	void 			_printLog(string str);
	void 			_sendMessage(int socket, char * msg);
	
	void 			_closeConnection(int socket_index);
	void 			_closeAllConnections();
	
	sockaddr_in & 		_servAddr();
	int & 			_baseSocket();

	int 			_processAndSend(int socket_code, int socket_index, sockaddr_in addrinfo, int & stop_signal);
public:
	Server(const char * logfile_name = "CONSOLE", int port = DEFAULT_PORT);
	~Server();
	
	int  start(const char * datafile_name = "data.txt");
	void printData(ostream * file = &cout);	
};

#endif
