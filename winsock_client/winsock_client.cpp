// socket_test.cpp : Defines the entry point for the console application.
//


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "stdafx.h"
#include"Request_protocol.h"
#include<iostream>
#include<fstream>

#pragma comment(lib, "Ws2_32.lib")

void fileRead(const char* fn,std::string &fdata)
{
	char buff[100];
	std::ifstream myReadFile;
	myReadFile.open(fn);
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile.getline(buff, 100);
			fdata.append(buff);
			fdata.append("\n");
		}
	}
	myReadFile.close();
}



int main(void)
{
	
	std::string send_data;
	fileRead("data.txt", send_data);  // elküldendõ üzenet
	
	try{
	Request_protocol r_mail;
	r_mail.connectTo("localhost",8888);
	r_mail.connectRe();
	r_mail.mailFrom("csabi@mail.com");
	r_mail.mailFromRe();
	r_mail.mailTo("foo@mail.com");
	r_mail.mailToRe();
	r_mail.data(send_data);
	}
	catch(const char* s){
	std::cout<<s;
	}
	
	WSACleanup();
	system("PAUSE");
	return 0;
}

