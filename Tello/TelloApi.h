#ifndef TelloApi
#define TelloApi

#define local_ip "" 
#define local_port 8889
#define tello_port 8889
#define tello_state_port 8890
#define tello_ip "192.168.10.1"


#include <winsock2.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <Ws2tcpip.h>
#include <fstream>
#include <thread>
#include <ctime>

#pragma comment(lib, "Ws2_32.lib")

struct Coordinates
{

	int x;
	int y;
	int z;

};


class Tello {

private:
	int speed;
	const float maxTimeout = 15;


public:
	Tello(int v) : speed(v) {
	}


	WSADATA WSAData;										// Used for WSA Startup - to indicate the use of sockets
	SOCKET socket_tello;									// Socket to connect to tello
	SOCKET socket_tello_state;								// Socket to receive info about the state of Tello 

	struct sockaddr_in client_addr = {};					// structure for handling internet addresses - for client
	struct sockaddr_in server_addr = {};					// structure for handling internet addresses - for server
	struct sockaddr_in tello_addr;
	struct sockaddr_in tello_state = {};					// structure for handling internet addresses - for tello state

	char buf[1024];
	
	bool initialise();
	bool move(struct Coordinates point);
	bool land();
	void takeoff();
	void delay(float duration);
	void arm(bool check);
	void receiveThread();
	bool sendCommand(std::string command);
};

#endif#pragma once
