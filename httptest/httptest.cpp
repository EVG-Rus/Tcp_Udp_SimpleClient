

#include <iostream>


#define _WINSOCKAPI_
#pragma comment(lib, "Ws2_32.lib")

#include "HTTPRequest.hpp"
#include "json.hpp"
#include "SockTcpUdp.hpp"

bool sendPOSTRequest() {
	try {
		http::Request request("tcp://127.111.0.1:3001");
		std::map<std::string, std::string> parameters = { { "plate", "123" } };
		const http::Response response = request.send("POST", parameters, {
			"Content-Type: application/x-www-form-urlencoded" });
	}
	catch (const std::exception& e) {

	}
	return true;
}

bool sendGetRequest() {
	try {
		http::Request request(std::string("127.0.0.1:3001") + "?plate=" + "456");
		const http::Response response = request.send();
	}
	catch (const std::exception& e) {

	}
	return true;
}


int main()
{
	std::string urlval = "tcp://127.0.0.2/err";
	std::string protocolval = "";
	std::string hostval = "";
	std::string portval = "";
	std::string resrcval = "";
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

	cout << protocolval << endl;
	cout << hostval << endl;
	cout << portval << endl;
	cout << resrcval << endl;

	return 0;

//	SendTcp("127.0.0.1", 3001, "udp");
}

