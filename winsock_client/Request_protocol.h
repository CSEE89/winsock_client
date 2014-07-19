//E-mail küldési kérés protokollja TCP fölött

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include<iostream>
#include<string>

#define connectOK "connect ok \r\n"
#define mailtoOK "mailto ok \r\n"
#define mailfromOK "mailfrom ok \r\n" 
#define dataOK "data end \r\n"
#define MF "MAIL FROM"
#define MT "MAIL TO"
#define DT "DATA"
#define SP " "
#define CRLF "\r\n"



class Request_protocol{
	WSADATA WsaDat;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
public:
	Request_protocol();
	~Request_protocol();
	void connectTo(const char *host,int port);
	void mailFrom(const char* c);
	void mailTo(const char* c);
	void data(const std::string &s);

	bool connectRe();
	bool mailFromRe();
	bool mailToRe();
	bool dataRe();
private:
	bool responcheck(const std::string c);
};