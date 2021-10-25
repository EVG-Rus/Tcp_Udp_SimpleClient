#pragma once

#ifndef		__SOCK_TCPUDP_H__
#define		__SOCK_TCPUDP_H__

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>


void parseUrlToParts(std::string urlval, std::string &protocolval, std::string &hostval, std::string &portval, std::string &resrcval) {
	protocolval = hostval = portval = resrcval = "";
	bool setportval = false;
	int nposval = urlval.find_first_of("//");
	if (nposval > -1) {
		protocolval = urlval.substr(0, nposval - 1);
		urlval = urlval.substr(nposval + 2);
	}
	nposval = urlval.find_first_of(":");
	if (nposval > -1) {
		hostval = urlval.substr(0, nposval);
		urlval = urlval.substr(nposval + 1);
	}
	else {
		setportval = true;
	}
	nposval = urlval.find_first_of("/");
	if (nposval > -1) {
		if (setportval) {
			hostval = urlval.substr(0, nposval);
			resrcval = urlval.substr(nposval + 1);
		}
		else {
			portval = urlval.substr(0, nposval);
			resrcval = urlval.substr(nposval + 1);
		}
	}
	else {
		if (setportval) {
			hostval = urlval;
		}
		else {
			portval = urlval;
		}
	}
}


int SendTcp(std::string hosturl, int portval, std::string infoval)
{
	WSADATA wsa_data;
	SOCKADDR_IN addr;

	WSAStartup(MAKEWORD(2, 0), &wsa_data);
	const auto server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	InetPtonA(AF_INET, hosturl.c_str(), &addr.sin_addr.s_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(portval);

	int conresval = connect(server, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr));
	if (conresval != 0) {
		closesocket(server);
		WSACleanup();
		return conresval;
	}
	send(server, infoval.c_str(), infoval.length(), 0);

	closesocket(server);
	WSACleanup();
	return conresval;
}


int SendUdp(std::string hosturl, int portval, std::string infoval)
{
	WSADATA wsa_data;
	SOCKADDR_IN addr;

	WSAStartup(MAKEWORD(2, 0), &wsa_data);
	const auto server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	InetPtonA(AF_INET, hosturl.c_str(), &addr.sin_addr.s_addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(portval);

	int conresval = connect(server, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr));
	if (conresval != 0) {
		closesocket(server);
		WSACleanup();
		return conresval;
	}
	send(server, infoval.c_str(), infoval.length(), 0);

	closesocket(server);
	WSACleanup();
	return conresval;
}



#endif
