#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdlib>

#include "../Libraries/MainLib.h"

class Client
{
private:
	int 		_socket;
	int		_port;
	sockaddr_in	_serv_addr;
	hostent *	_hp;
	
	Coder		_coder;
public:
	Client(const char * address = DEFAULT_ADDRESS, int _port = DEFAULT_PORT);
	
	~Client()
	{
		
	}
	
	int start(char * request);
	int startHTML(char * request, char * filename);
};

#endif
