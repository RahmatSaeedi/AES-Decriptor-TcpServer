#pragma once
#include <WS2tcpip.h>
#include "Logger.h"


#pragma comment (lib, "ws2_32.lib")

using namespace std;

class Tcp_Server
{
private:
	SOCKET _socket;
	Logger * logger = new Logger(LoggerLocation::CONSOLE, Language::ENGLISH);
public:
	Tcp_Server(int port);
	~Tcp_Server();



	void Send(char* , int, int = 0);
	int Recieve(char*, int, int = 0);
};