#include "TelloApi.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{

	ifstream command_file("command.txt");
	string delay_time;
	int sec;
	string command;
	int drone_speed;

	cout << "Set Drone Speed: Enter Drone Speeds between 10-100 cm/s" << endl;
	cin >> drone_speed;
	if (drone_speed < 10 || drone_speed > 100)
	{
		do
		{
			cout << "Warning: Enter integer speed within range 10-100" << endl;
			cin >> drone_speed;
		} while (drone_speed < 10 || drone_speed > 100);
	}
	
	Tello drone(drone_speed);

	/* Initialise socket communication with Tello drone */
	if (drone.initialise())
	{
		cout << "Drone Initializing done" << endl;
	}
	else
	{
		cout << "Initialization failed" << endl;
		return -1;

	}

	/* Arm the drone */
	drone.arm(true); 

	/* Press any key to begin */
	cout << "Press any key to begin" << endl;
	_getch();

	/* Lift off drone */
	cout << "Drone taking off.. " << endl;
	drone.takeoff();

	if (command_file.is_open())
	{
		cout << "Reading commands from command.txt file" << endl;

		while (getline(command_file, command))
		{
			if (command.find("delay") == 0)
			{
				delay_time = command.substr(5, command.find(" "));
				istringstream(delay_time) >> sec;
				sec = sec * 1000;
				cout << "Delay for " << delay_time << " seconds" << endl;
				Sleep(sec);
			}
			else
			{
				cout << command << endl;
				drone.sendCommand(command);
			}

		}
	}

	return 0;

}