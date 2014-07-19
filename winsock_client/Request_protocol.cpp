#include "stdafx.h"
#include"Request_protocol.h"
bool compare(const char* c1, const char* c2){

	int len = strlen(c1) < strlen(c2) ? strlen(c1) : strlen(c2);
	for (short i = 0; i < len; i++){
		if (c1[i] != c2[i]) return false;
	}
	if (len == 0) return false;
	return true;
};
Request_protocol::Request_protocol(){
	
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		WSACleanup();
		throw "WSA Initialization failed!\r\n";
	}

	// Create our socket

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		WSACleanup();
		throw "Socket creation failed.\r\n";
	}	
};
Request_protocol::~Request_protocol(){

	shutdown(Socket, SD_SEND);
	closesocket(Socket);
	WSACleanup();
};
void Request_protocol::connectTo(const char* hosti,int port){
	// Resolve IP address for hostname
	struct hostent *host;
	if ((host = gethostbyname(hosti)) == NULL)
	{
		WSACleanup();
		throw "Failed to resolve hostname.\r\n";
	}

	// Setup our socket address structure

	SockAddr.sin_port = htons(port);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		WSACleanup();
		throw "Failed to establish connection with server\r\n";
	}

};
void Request_protocol::mailFrom(const char* c){
	std::string s;
	s =std::string(MF) + std::string(SP)+std::string(c)+std::string(CRLF);
	send(Socket, s.c_str(), s.size(), 0);
};
void Request_protocol::mailTo(const char* c){
	std::string s;
	s = std::string(MT) + std::string(SP) + std::string(c) + std::string(CRLF);
	send(Socket, s.c_str(), s.size(), 0);
};
void Request_protocol::data(const std::string &c){
	std::string s;
	s = std::string(DT) + std::string(SP) + c + std::string(CRLF);
	send(Socket, s.c_str(), s.size(), 0);
};

bool Request_protocol::connectRe(){
	if (responcheck(connectOK))
		return true;
	throw "Protocol error";
};
bool Request_protocol::mailFromRe(){
	if (responcheck(mailfromOK))
		return true;
	throw "Mail error";
};
bool Request_protocol::mailToRe(){
	if (responcheck(mailtoOK))
		return true;
	throw "Mail to error";
};
bool Request_protocol::dataRe(){
	if (responcheck(dataOK))
		return true;
	throw "wrong data";
};
bool Request_protocol::responcheck(const std::string c){
	char inbuff[100];
	memset(inbuff, 0, 100);
	recv(Socket, inbuff, 100, 0);
	std::string s(inbuff, strnlen(inbuff,100));
	//if (compare(inbuff,c))
	if (c.compare(s)==0)
		return true;
	return false;
};