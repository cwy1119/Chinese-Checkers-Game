#include "Messager.h"
#include<WS2tcpip.h>
#include<iostream>
using std::cout;
using std::endl;


Messager::Messager()
{
}

Messager::Messager(string ip, unsigned port)
{
	this->ip = ip;
	this->port = port;
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		cout << "¼ÓÔØ¿âº¯ÊýÊ§°Ü!" << endl;
	}
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

bool Messager::connectServer()
{
	SOCKADDR_IN serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(this->port);
	inet_pton(AF_INET, TEXT(this->ip.c_str()), &serAddr.sin_addr.s_addr);
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{  
		cout << "Á¬½ÓÊ§°Ü!";
		closesocket(sclient);
		return false;
	}
	
	return true;
}

void Messager::sendMessage(string data)
{
	const char* Data = data.c_str();
	send(sclient, Data, strlen(Data), 0);
	
}

string Messager::receiveMessage()
{
	char Data[255];
	int ret = recv(sclient, Data, 255, 0);
	if (ret > 0) {
		Data[ret] = 0x00;
	}
	string result;
	result.append(Data);
	return result;
}


Messager::~Messager()
{
}
