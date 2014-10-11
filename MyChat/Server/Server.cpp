// Server.cpp : Defines the entry point for the console application.
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
const int MAX_CLIENTS = 10;

class Client {
public:
	Client(SOCKET socket, DWORD threadInfo);
	~Client();
	void setData(string data);
	bool needSend();
	bool receive(char* buffer);
	void sendData();
	DWORD threadInfo;
	void setUpdateNow();
private:
	string received;
	bool freshReceived;
	SOCKET socket;
	bool sendNow;
	bool test;
};

class Server {
public:
	Server();
	~Server();
	void init();
	void close();
	void acceptClients();
	void addClient(Client* client);
	void updateClients();
private:
	int numberClients;
	Client** clients;
	SOCKET socketID;
	static DWORD WINAPI acceptThread(LPVOID serverLink);
	static DWORD WINAPI clientThread(LPVOID client);
};

class ServerException {
public:
	ServerException(string errorMessage, int errorNumber=0);
	~ServerException();
	string getError();
	int getNumberError();
private:
	string error;
	int numberError;
};

ServerException::ServerException(string errorMessage, int errorNumber) {
	ServerException::error = errorMessage;
	ServerException::numberError = errorNumber;
}

string ServerException::getError() {
	return ServerException::error;
}

int ServerException::getNumberError() {
	return ServerException::numberError;
}

Server::Server() {
	Server::clients = new Client*[MAX_CLIENTS];
}

Server::~Server() {
	
}

void Server::updateClients() {
	for(int i=0; i<Server::numberClients; i++) {
		Server::clients[i]->setUpdateNow();
	}
}

void Server::addClient(Client* client) {
	Server::clients[Server::numberClients] = client;
}

void Server::init() {
	try {
		char socksInfo[1024];
		if(WSAStartup(0x0202, (WSADATA *) &socksInfo[0])) throw new ServerException("Server init error: "+WSAGetLastError());

		SOCKET serverSocket;
		if(!(serverSocket=socket(AF_INET, SOCK_STREAM, 0))) {
			throw new ServerException("Create socket error", WSAGetLastError());
		}

		sockaddr_in listenAddr;
		listenAddr.sin_family = AF_INET;
		listenAddr.sin_addr.s_addr = 0;
		listenAddr.sin_port = SERVER_PORT;
		if(bind(serverSocket, (sockaddr*) &listenAddr, sizeof(listenAddr))) {
			closesocket(serverSocket);
			throw new ServerException("Socket bind error", WSAGetLastError());
		}
		if(listen(serverSocket, 0x100)) {
			closesocket(serverSocket);
			throw new ServerException("Socket listen error", WSAGetLastError());
		}

		Server::numberClients = 0;
		Server::socketID = serverSocket;
		cout << "Server was successfully initialized" << endl;
	}
	catch(ServerException* e) {
		cout << e->getError() << " (Number: " << e->getNumberError() << ")";
		WSACleanup();
		//delete e; !!!
	}
}

void Server::close() {
	// close sockets, disconnect clients
	cout << "Server shutdown!" << endl;
}

void Server::acceptClients() {
	DWORD acceptThreadInfo;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Server::acceptThread, this, NULL, &acceptThreadInfo);
}

DWORD WINAPI Server::acceptThread(LPVOID serverLink) {
	Server* server = (Server*)serverLink;
	SOCKET serverSocket = server->socketID;
	SOCKET clientSocket;
	sockaddr_in clientAddr;
	int clientAddrSize = sizeof(clientAddr);
	while(clientSocket=accept(serverSocket, (sockaddr*) &clientAddr, &clientAddrSize)) {
		server->numberClients++;
		HOSTENT* clientHost;
		clientHost = gethostbyaddr((char*)&clientAddr.sin_addr.s_addr, 4, AF_INET);
		cout << clientHost << " connected now!" << endl;
		DWORD clientThreadInfo = 1;
		Client* client = new Client(clientSocket, clientThreadInfo);
		server->addClient(client);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Server::clientThread, client, NULL, &client->threadInfo);
	}
	return 0;
}

DWORD WINAPI Server::clientThread(LPVOID client) {
	char receiveBuffer[1024*20];
	Client* pClient = (Client*)client;
	while(pClient->receive(receiveBuffer)) {
		pClient->setData(receiveBuffer);
		if(pClient->needSend()) pClient->sendData();
	}
	return 0;
}

class Data {
public:
	Data();
	~Data();
private:
};

class Message: public Data {
public:
	Message();
	~Message();
private:
};

Client::Client(SOCKET socket, DWORD threadInfo) {
	Client::socket = socket;
	Client::threadInfo = threadInfo;
	Client::sendNow = false;
}

Client::~Client() {

}

void Client::setData(string data) {
	Client::received = data;
	Client::freshReceived = true;
}

bool Client::needSend() {
	/*if(Client::sendNow == true) {
		Client::sendNow = false;
		return true;
	} else {
		return false;
	}*/
	return false;
}

bool Client::receive(char* buffer) {
	int receiveBytes = recv(Client::socket, &buffer[0], sizeof(buffer), NULL);
	if(receiveBytes && receiveBytes != SOCKET_ERROR)
		return true;
	else cout << "RECEIVE ERROR!";
}

void Client::sendData() {
	char* buffer = "a";
	send(Client::socket, buffer, sizeof(buffer), NULL);
}

void Client::setUpdateNow() {
	//Client::sendNow = true;
	Client::test = true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Server server;
	server.init();
	server.acceptClients();
	while(true) {
		server.updateClients();
		Sleep(1000);
	}
	server.close();
	return 0;
}