#ifndef MESSAGER_H
#define MESSAGER_H
#include<string>
#include<WINSOCK2.H>
#pragma comment(lib,"ws2_32.lib")
using std::string;
class Messager
{
public:
	Messager();
	Messager(string ip, unsigned port = 13455);
	bool connectServer();
	void sendMessage(string data);
	string receiveMessage();
	~Messager();
private:
	string ip;
	unsigned port;
	SOCKET sclient;
};
#endif

