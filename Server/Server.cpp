#include "Server.h"

#define _DEBUG_

using namespace std;

Server::Server(const char * _logFile_name, int port)
{
	if (string(_logFile_name) != "CONSOLE")
	{
		cout << "AAA" << endl;
		_fb.open(_logFile_name, ios::out);
		_logFile = new ostream(&_fb);
	}
	else
		_logFile = &std::cout;
	
	try
	{
		_initServer(port);
	}
	catch (runtime_error err)
	{
		*_logFile << err.what() << endl;
	}
	
	_clientsNum = 0;
	_clientsSuccessNum = 0;
	_requestsNum = 0;
	_requestsSuccessNum = 0;
	
	time_t seconds = time(NULL);
	tm * timeinfo = localtime(&seconds);
	if (_logFile != &std::cout)
	{
		cout << asctime(timeinfo);
		cout << "Server initialized" << endl;
		cout << "Server IP : " << inet_ntoa(_servAddr().sin_addr) << endl;
		cout << "Server port : " << _servAddr().sin_port << endl << endl;
		cout << "_logFile : " << _logFile_name << endl << endl;
	}
	
	_printCurrentTime();
	*_logFile << "Server initialized" << endl;
	*_logFile << "Server IP : " << inet_ntoa(_servAddr().sin_addr) << endl;
	*_logFile << "Server port : " << _servAddr().sin_port << endl << endl;
}

/* ------------------------------------------- */

Server::~Server()
{
	time_t 	seconds;
	_printCurrentTime();
	*_logFile << "Finishing work..." << endl;
	*_logFile << "Client processed : " << endl;
	*_logFile << "\tTotal : " << _clientsNum << endl;
	*_logFile << "\tSucceeded : " << _clientsSuccessNum << endl;
	*_logFile << "Requests processed : " << endl;
	*_logFile << "\tTotal : " << _clientsNum << endl;
	*_logFile << "\tSucceeded : " << _clientsSuccessNum << endl;

	if (_logFile != &std::cout)
	{
		seconds = time(NULL);
		tm * timeinfo = localtime(&seconds);
		cout << asctime(timeinfo);
	
		cout << "Finishing work..." << endl;
		cout << "Client processed : " << endl;
		cout << "\tTotal : " << _clientsNum << endl;
		cout << "\tSucceeded : " << _clientsSuccessNum << endl;
		cout << "Requests processed : " << endl;
		cout << "\tTotal : " << _clientsNum << endl;
		cout << "\tSucceeded : " << _clientsSuccessNum << endl;
	}
	if (_fb.is_open())
		_fb.close();
}

/* ------------------------------------------- */

void Server::_initServer(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == -1)
	{
		throw runtime_error("Cannot create base socket!");
	}
	_maxSocketNumber = sock;
	_basePort = port;
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(_basePort);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	int on = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) == -1) 
	{
	    	throw runtime_error("Port already in usage!");
	}
	
	if (bind(sock, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		throw runtime_error("Error using bind()");
	}
	_addrinfoVector.push_back(server_addr);
	_socketVector.push_back(sock);
}

/* ------------------------------------------- */
	
void Server::_printCurrentTime()
{
	time_t seconds = time(NULL);
	tm * timeinfo = localtime(&seconds);
	*_logFile << asctime(timeinfo);
}

/* ------------------------------------------- */

void Server::_printLog(string str)
{
	_printCurrentTime();
	*_logFile << str << endl << endl;
}

/* ------------------------------------------- */

void Server::_sendMessage(int socket, char * msg)
{
	(void)socket;
	(void)msg;
}

/* ------------------------------------------- */

void Server::_closeConnection(int socket_index)
{
	if (socket_index < 0 || socket_index >= (int)_socketVector.size())
	{
		throw runtime_error("Wrong client index, cannot close connection!");
	}

	_printCurrentTime();
	*_logFile << "Closing connection with client" << endl;
	*_logFile << "Client IP : " << inet_ntoa(_addrinfoVector[socket_index].sin_addr) << endl;
	*_logFile << "Client port : " << _addrinfoVector[socket_index].sin_port << endl << endl;
	
	_socketVector.erase(_socketVector.begin() + socket_index);
	_addrinfoVector.erase(_addrinfoVector.begin() + socket_index);
	close(_socketVector[socket_index]);
}

/* ------------------------------------------- */

void Server::_closeAllConnections()
{
	while (_socketVector.size() > 0)
		_closeConnection(_socketVector.size() - 1);
}

/* ------------------------------------------- */

sockaddr_in & Server::_servAddr()
{
	return _addrinfoVector[0];
}

/* ------------------------------------------- */

int & Server::_baseSocket()
{
	return _socketVector[0];
}

/* ------------------------------------------- */

int Server::_processAndSend(int socket_code, int socket_index, sockaddr_in addrinfo, int & stop_signal)
{
	int 	message_len;
	char * 	buff = new char[BUFF_SIZE];
	
	stop_signal = 0;
	
	read(socket_code, &message_len, sizeof(int));
	buff[message_len] = '\0';
	
	if (message_len < 0 || message_len >= BUFF_SIZE)
	{
		_printCurrentTime();
		*_logFile << "Error recieving from " << inet_ntoa(addrinfo.sin_addr) << ":";
		*_logFile << addrinfo.sin_port << endl;
		*_logFile << "Bad message length : " << message_len << endl << endl;
	}
	else
	{
		read(socket_code, buff, message_len);
		buff[message_len] = '\0';
		
		if (strcmp(buff, "stop") == 0)
		{
			_printCurrentTime();
			*_logFile << "Stop signal recieved from " << inet_ntoa(addrinfo.sin_addr) << ":";
			*_logFile << addrinfo.sin_port << endl << endl;
			
			stop_signal = STOP_SERVER;
			write(socket_code, &stop_signal, sizeof(int));
			
			_closeAllConnections();
			delete [] buff;
			return 1;
		}
			
		_printCurrentTime();
		*_logFile << "Message recieved from " << inet_ntoa(addrinfo.sin_addr) << ":";
		*_logFile << addrinfo.sin_port << endl;
		*_logFile << buff << endl << endl;
		
		string request = string(buff);
						
		vector<Purchase> * 	temp_vec;
		int			datasize;
		
		datasize = 0;
		temp_vec = _dataBase.processRequest(request);
		
		int request_type = temp_vec ? CORRECT : INCORRECT;
		write(socket_code, &request_type, sizeof(int));
		
		delete [] buff;
		int code_len = 0;
		if (request_type == CORRECT)
		{
			int records = temp_vec->size();
			write(socket_code, &records, sizeof(int));
			
			for (vector<Purchase>::iterator iter = temp_vec->begin(); iter != temp_vec->end(); ++iter)
			{
				code_len = 2 * sizeof(int) + sizeof(double) + DATE_LEN + strlen((*iter).item);
				write(socket_code, &code_len, sizeof(int));
				datasize += sizeof(int);
				buff = _coder.getCodeByPurchase(*iter);
				write(socket_code, buff, code_len);
				datasize += code_len;
				delete [] buff;
			}
			delete temp_vec;
		}
		
		_printCurrentTime();	
		*_logFile << "Data sent to " << inet_ntoa(addrinfo.sin_addr) << ":";
		*_logFile << addrinfo.sin_port << endl;	
		*_logFile << "Total size : " << datasize << " bytes" << endl << endl;	
			
		if (socket_index != -1)
			_closeConnection(socket_index);
	}
	return 1;
}

/* ------------------------------------------------ */

int Server::start(const char * datafile_name)
{	
	_printCurrentTime();
	*_logFile << "Start reading data from : " << datafile_name << endl << endl;
	int rc = _dataBase.readData(datafile_name);
	_printCurrentTime();
	*_logFile << "Reading complete." << endl;
	*_logFile << "Total records : " << rc << endl << endl;
	
	//printData();
	
	fd_set for_read;
	fd_set for_write;
	fd_set with_exceptions;
        
        // TODO :
        // Organize sending process : separate generaing (selecting) and sendid data
	
	FD_ZERO(&for_read);
	FD_ZERO(&for_write);
	FD_ZERO(&with_exceptions);
	FD_SET(_baseSocket(), &for_read);
	
	int new_socket;
	int some_activity;
	
	listen(_baseSocket(), MESSAGE_QUEUE_LENGTH);
	while (true)
	{
		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 50000;
		FD_ZERO(&for_read);
		FD_ZERO(&for_write);
		FD_ZERO(&with_exceptions);
		FD_SET(_baseSocket(), &for_read);
		some_activity = select(_maxSocketNumber + 1, &for_read, &for_write, &with_exceptions, &timeout);
		
		sockaddr_in 	temp_addrinfo;
		int		addr_len;
		
		if (some_activity > 0)
		{
			if (FD_ISSET(_baseSocket(), &with_exceptions))
			{
				_printCurrentTime();
				*_logFile << "Base socket is broken!" << endl << endl;
				_closeAllConnections();
				return -1;
			}
			else if (FD_ISSET(_baseSocket(), &for_read))
			{
				new_socket = accept(_baseSocket(), (sockaddr *)&temp_addrinfo, (socklen_t *)&addr_len);
				++_clientsNum;
				
				if (new_socket == -1)
				{
					_printCurrentTime();
					*_logFile << "Connection failure!" << endl << endl;
				}
				else
				{
					_maxSocketNumber = new_socket > _maxSocketNumber ? new_socket : _maxSocketNumber;
				
					_printCurrentTime();
					*_logFile << "New client connected" << endl;
					*_logFile << "Client IP : " << inet_ntoa(temp_addrinfo.sin_addr) << endl;
					*_logFile << "Client port : " << temp_addrinfo.sin_port << endl << endl;
					++_clientsSuccessNum;
				
					_addrinfoVector.push_back(temp_addrinfo);
					_socketVector.push_back(new_socket);
					FD_SET(new_socket, &for_read);
				}
				
			}
		
			for (int i = 1; i < (int)(_socketVector.size()); ++i)
			{
				if (FD_ISSET(_socketVector[i], &with_exceptions))
				{
					_printCurrentTime();
					_closeConnection(i);
					--i;
				}
				else if (FD_ISSET(_socketVector[i], &for_read))
				{
					++_requestsNum;
					int stop_signal;
					_requestsSuccessNum += _processAndSend(_socketVector[i], i, _addrinfoVector[i], stop_signal);
					if (stop_signal)
						return 0;
					--i;	
				}
			
			}
		}
	}
	return 0;
}

/* ------------------------------------------- */

void Server::printData(ostream * file)
{
	_dataBase.printData(file);
}

