#include "TCP_Server.h"


Tcp_Server::Tcp_Server(int port)
{
	//Initialize WinSock
	WSADATA wsaData;
	WORD TCP_Version = MAKEWORD(2, 2);


	if (WSAStartup(TCP_Version, &wsaData) != 0) {
		logger->Log(Message::CAN_NOT_INITIALIZE_WINSOCK);
		return;
	}

	//Create Socket (Endpoint)
	SOCKET TCP_Server = socket(AF_INET, SOCK_STREAM, 0);
	if (TCP_Server == INVALID_SOCKET)
	{
		logger->Log(Message::CAN_NOT_CREATE_SOCKET);
		return;
	}


	//Bind IP & port to a Socket
	sockaddr_in TCP_Server_Setting;
	TCP_Server_Setting.sin_family = AF_INET;
	TCP_Server_Setting.sin_port = htons(port);
	TCP_Server_Setting.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(TCP_Server, (sockaddr*)&TCP_Server_Setting, sizeof(TCP_Server_Setting));

	//Tell Winsock the Socket is for listening
	listen(TCP_Server, SOMAXCONN);


	//Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);
	_socket = accept(TCP_Server, (sockaddr*)&client, &clientSize);
	if (_socket == INVALID_SOCKET)
	{
		logger->Log(Message::CLIENT_SOCKET_IS_INVALID);
		return;
	}
}


Tcp_Server::~Tcp_Server()
{
	//Close Socket
	closesocket(_socket);

	//cleanup Winsock
	WSACleanup();
}

void Tcp_Server::Send(char * message, int messageLength, int flags) {
	send(_socket, (char*)message, messageLength, flags);
}

int Tcp_Server::Recieve(char* messageBuffer, int bufferLength, int flags) {
	int bytesRecieved = recv(_socket, (char*)messageBuffer, bufferLength, flags);
	if (bytesRecieved == SOCKET_ERROR) {
		logger->Log(Message::SOCKET_ERROR_WHILE_RECIEVING_DATA);
		return 0;
	}
	else {
		return bytesRecieved;
	}
}