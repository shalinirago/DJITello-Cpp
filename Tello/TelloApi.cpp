#include "TelloApi.h"

using namespace std;

void Tello::receiveThread()
{
	/* Runs as a Thread to receive responses from Tello */
	cout << "Receive from tello thread initiated" << endl;

	/* buf holds the datagram received from Tello */
	memset(buf, 0, sizeof(buf));

	int tello_addr_length = sizeof(tello_addr);
	while (true)
	{
		if ((recvfrom(socket_tello, buf, sizeof(buf), 0, (sockaddr *)&tello_addr, &tello_addr_length)) == SOCKET_ERROR)
		{
			cout << "Failed to receive command with error code: " << WSAGetLastError() << endl;
		}

	}

}

bool Tello::initialise()
{
	bool success;

	/* Initialize Winsock - All processes (applications or DLLs)
	that call Winsock functions must initialize the use of the Windows Sockets DLL before making other Winsock functions calls */
	int result = WSAStartup(MAKEWORD(2, 2), &WSAData);
	if (result != 0)
	{
		cout << "WSAStartup failed: " << result << endl;
	}
	cout << "Winsock successfully initialized" << endl;

	this_thread::sleep_for(chrono::duration<double>(2));

	/* Defining the client address structure */
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(local_port);
	inet_pton(AF_INET, local_ip, &client_addr.sin_addr.s_addr);

	/* Defining the server address structure */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(tello_port);							   // convert the port value to hex 
	inet_pton(AF_INET, tello_ip, &server_addr.sin_addr);

	this_thread::sleep_for(chrono::duration<double>(2));

	/* Creating a socket */
	cout << "Creating a socket... " << endl;
	socket_tello = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);				//socket(IPv4, socket type using UDP, The UDP)
	/* Checking if socket created is valid*/
	if (socket_tello == INVALID_SOCKET)
	{
		cout << "Error at socket(): " << WSAGetLastError() << endl;
	}

	cout << "Socket successfully created" << endl;

	/* Bind to socket */
	this_thread::sleep_for(chrono::duration<double>(2));
	cout << "Binding local address with socket: " << endl;
	/* Binding the socket to the local address and port */
	if (::bind(socket_tello, (sockaddr *)&client_addr, sizeof(client_addr)) == SOCKET_ERROR)
	{
		cout << "Binding of socket failed with error code: " << WSAGetLastError() << endl;
	}
	cout << "Binding successful" << endl;


	/* Start receive_thread */
	thread receive_thread_tello(&Tello::receiveThread, this);				// requires an instance to be called
	receive_thread_tello.detach();											// .detach() ensures that the thread runs simultaneously and separately from the main thread
	success = true;

	return success;
}

bool Tello::sendCommand(string command)
{
	clock_t send_time = clock();
	char send_cmd[1024];
	bool success;
	/* In order to send command of the utf-8 format, it is converted to type char* and sent using sendto function */
	strcpy_s(send_cmd, sizeof(send_cmd), command.c_str());
	cout << "Sending command: " << send_cmd << " to Tello at " << tello_ip << endl;
	if (sendto(socket_tello, send_cmd, (int)strlen(send_cmd), 0, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		cout << "Failed to send command with error code: " << WSAGetLastError() << endl;
		//WSACleanup();
	}
	clock_t sent_time = clock();

	cout << "Took: " << (sent_time - send_time) / CLOCKS_PER_SEC << " to send command " << endl;
	
	clock_t start_time = clock();
	/* Waits for maximum timeout to occur when awaiting response from Tello */
	cout << "Attempting to receive ack from Tello..." << endl;
	while (buf[0] == '\0')
	{
		if (((clock() - start_time) / CLOCKS_PER_SEC) > maxTimeout)
		{
			cout << "Max timeout exceeded for command: " << send_cmd << endl;
			success = false;
			return success;
		}
	}

	cout << "Successfully sent command: " << send_cmd << " to Tello at " << tello_ip << endl;
	cout << "Response from tello: " << buf << endl;
	
	clock_t recv_time = clock();
	cout << " Took : " << (recv_time - send_time) / CLOCKS_PER_SEC << " to receive command " << endl;
	
	memset(buf, 0, sizeof(buf));								//clear out buffer

	success = true;
	
	return success;
}

bool Tello::land()
{
	bool success;
	if (sendCommand("land"))
	{
		cout << "Drone Landed" << endl;
		success = true;
	}
	else
	{
		cout << " Error occurred when landing" << endl;
		success = false;
	}

	return success;
}

void Tello::takeoff()
{
	if (sendCommand("takeoff"))
	{
		cout << "Drone tookoff successfully" << endl;
	}
	else
	{
		cout << " Error occurred when taking off" << endl;
	}
}

void Tello::arm(bool check)
{
	/* Before any commands are sent to Tello, it must be sent "command" to engage the motors */
	if (check)
	{
		if (sendCommand("command"))
		{
			cout << "Drone armed" << endl;
		}
		else
			cout << " Error occurred when arming Drone" << endl;

		/* Set speed for drone as given by user */
		string set_speed = "speed " + to_string(speed);
		if (sendCommand(set_speed))
		{
			cout << "Speed set to " << speed << endl;
		}
		else
			cout << "Error setting speed" << endl;

	}


}

void Tello::delay(float duration)
{
	/* To provide delays between commands sent out to tello */
	this_thread::sleep_for(chrono::duration<double>(duration));

}

bool Tello::move(struct Coordinates point)
{
	bool success;
	/* corresponds to the go x y z speed command for tello */
	cout << "Moving to co-ordinates: " << point.x << " " << point.y << " " << point.z << " with speed: " << speed << endl;
	if (sendCommand("go " + to_string(abs(point.x)) + " " + to_string(abs(point.y)) + " " + to_string(abs(point.z)) + " " + to_string(speed)))
	{
		success = true;
		return success;
	}
	else
	{
		success = false;
		return success;
	}
}

