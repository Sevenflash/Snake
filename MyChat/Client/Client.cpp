// Client.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

const int SERVER_IP = inet_addr("127.0.0.1");
const int SERVER_PORT = htons(3000);

class Client {
public:
	Client();
	~Client();
	void init();
	void close();
	void watch();
	void sendToServer(char* c);
private:
	int numberClients;
	SOCKET socketID;
	SOCKET serverSocket;
	static DWORD WINAPI watchThread(LPVOID serverLink);
};

class ClientException {
public:
	ClientException(string errorMessage, int errorNumber=0);
	~ClientException();
	string getError();
	int getNumberError();
private:
	string error;
	int numberError;
};

ClientException::ClientException(string errorMessage, int errorNumber) {
	ClientException::error = errorMessage;
	ClientException::numberError = errorNumber;
}

string ClientException::getError() {
	return ClientException::error;
}

int ClientException::getNumberError() {
	return ClientException::numberError;
}

Client::Client() {
}

Client::~Client() {
	
}

void Client::init() {
	try {
		char socksInfo[1024];
		if(WSAStartup(0x0202, (WSADATA *) &socksInfo[0])) throw new ClientException("Client init error: "+WSAGetLastError());

		SOCKET serverSocket;
		serverSocket = socket(AF_INET, SOCK_STREAM, 0);
		if(!serverSocket) throw new ClientException("Socket create error", WSAGetLastError());

		if(SERVER_IP==INADDR_NONE) throw new ClientException("Invalid server IP", WSAGetLastError());

		sockaddr_in connectAddr;
		connectAddr.sin_family = AF_INET;
		connectAddr.sin_addr.s_addr = SERVER_IP;
		connectAddr.sin_port = SERVER_PORT;
		HOSTENT* serverHost;

		if(connect(serverSocket, (sockaddr*)&connectAddr, sizeof(connectAddr)))
			throw new ClientException("Socket connect error", WSAGetLastError());

		Client::serverSocket = serverSocket;
	}
	catch(ClientException* e) {
		cout << e->getError() << " (Number: " << e->getNumberError() << ")";
		WSACleanup();
		//delete e; !!!
	}
}

void Client::close() {
	// close sockets, disconnect clients
	cout << "client shutdown!" << endl;
}

void Client::watch() {
	DWORD acceptThreadInfo;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Client::watchThread, this, NULL, &acceptThreadInfo);
}

DWORD WINAPI Client::watchThread(LPVOID serverLink) {

	return 0;
}

void Client::sendToServer(char* c) {
	send(Client::serverSocket, c, sizeof(c), NULL);
}

class Message {

};

class User {

};

int _tmain(int argc, _TCHAR* argv[])
{
	Client client;
	client.init();
	client.watch();
	while(int c = getch()) {
		client.sendToServer((char*)c);
	}
	client.close();
	return 0;
}