#include "TelloApi.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{

	int key = 0;
	string dist;
	string deg;
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

	/* Input control from user */
	/* Create a command panel to control the drone using keys on the keyboard */
	cout << "Following are the keys to control the drone using the keyboard " << endl;
	cout << "Press: <key> followed by a distance value (in cm) to move the drone " << endl;
	cout << "[key - Up] x move forward 'x' cm" << "\n" << "[key - Down] x move backward 'x' cm" << "\n"
		<< "[key - Left] x move left 'x' cm" << "\n" << "[key - Right] x move right 'x' cm" << "\n"
		<< "[key - w] x move up 'x' cm" << "\n" << "[key - s] x move down 'x' cm" << "\n"
		<< "[key - a] x rotate counter - clockwise by 'x' degree" << "\n"
		<< "[key - d] x rotate clockwise by 'x' degree" << "\n"
		<< "Esc to quit the control panel and land the drone " << endl;

	while (true)
	{
		key = 0;
		dist = " ";
		deg = " ";
		cout << "Enter key : " << endl;
		key = _getch();
		
		switch (key)
		{
		case 72:
			cout << "Enter distance in cm (20-500) " << endl;
			cin >> dist;
			if (stoi(dist) < 20 || stoi(dist) > 500)
			{
				do
				{
					cout << "Warning: Enter integer distance within range 20-500" << endl;
					cin >> dist;
				} while (stoi(dist) < 20 || stoi(dist) > 500);
			}
			command = "forward " + dist;
			if (drone.sendCommand(command))
			{
				cout << "Command 'forward' sent successfully" << endl;
			}
			else
			{
				cout << "Something went wrong!" << endl;
			}

			break;

		case 80:
			cout << "Enter distance in cm (20-500) " << endl;
			cin >> dist;
			if (stoi(dist) < 20 || stoi(dist) > 500)
			{
				do
				{
					cout << "Warning: Enter integer distance within range 20-500" << endl;
					cin >> dist;
				} while (stoi(dist) < 20 || stoi(dist) > 500);
			}			
			command = "back " + dist;
			if (drone.sendCommand(command))
			{
				cout << "Command 'back' sent successfully" << endl;
			}
			else
			{
				cout << "Something went wrong!" << endl;
			}

			break;

		case 75:
			cout << "Enter distance in cm (20-500) " << endl;
			cin >> dist;
			if (stoi(dist) < 20 || stoi(dist) > 500)
			{
				do
				{
					cout << "Warning: Enter integer distance within range 20-500" << endl;
					cin >> dist;
				} while (stoi(dist) < 20 || stoi(dist) > 500);
			}
			command = "left " + dist;
			if (drone.sendCommand(command))
			{
				cout << "Command 'left' sent successfully" << endl;
			}
			else
			{
				cout << "Something went wrong!" << endl;
			}

			break;

		case 77:
			cout << "Enter distance in cm (20-500) " << endl;
			cin >> dist;
			if (stoi(dist) < 20 || stoi(dist) > 500)
			{
				do
				{
					cout << "Warning: Enter integer distance within range 20-500" << endl;
					cin >> dist;
				} while (stoi(dist) < 20 || stoi(dist) > 500);
			}
			command = "right " + dist;
			if (drone.sendCommand(command))
			{
				cout << "Command 'right' sent successfully" << endl;
			}
			else
			{
				cout << "Something went wrong!" << endl;
			}

			break;

		case 119:
			cout << "Enter distance in cm (20-500) " << endl;
			cin >> dist;
			if (stoi(dist) < 20 || stoi(dist) > 500)
			{
				do
				{
					cout << "Warning: Enter integer distance within range 20-500" << endl;
					cin >> dist;
				} while (stoi(dist) < 20 || stoi(dist) > 500);
			}
			command = "up " + dist;
			if (drone.sendCommand(command))
			{
				cout << "Command 'up' sent successfully" << endl;
			}
			else
			{
				cout << "Something went wrong!" << endl;
			}

			break;

		case 115:
			cout << "Enter distance in cm (20-500) " << endl;
			cin >> dist;
			if (stoi(dist) < 20 || stoi(dist) > 500)
			{
				do
				{
					cout << "Warning: Enter integer distance within range 20-500" << endl;
					cin >> dist;
				} while (stoi(dist) < 20 || stoi(dist) > 500);
			}
			command = "down " + dist;
			if (drone.sendCommand(command))
			{
				cout << "Command 'down' sent successfully" << endl;
			}
			else
			{
				cout << "Something went wrong!" << endl;
			}

			break;

		case 100:
			cout << "Enter degree: (1-360) " << endl;
			cin >> deg;
			if (stoi(deg) < 1 || stoi(deg) > 360)
			{
				do
				{
					cout << "Warning: Enter integer degree within range 1-360" << endl;
					cin >> deg;
				} while (stoi(deg) < 20 || stoi(deg) > 500);
			}
			command = "cw " + deg;
			if (drone.sendCommand(command))
			{
				cout << "Command 'clockwise' sent successfully" << endl;
			}
			else
			{
				cout << "Something went wrong!" << endl;
			}

			break;

		case 97:
			cout << "Enter degree: (1-360) " << endl;
			cin >> deg;
			if (stoi(deg) < 1 || stoi(deg) > 360)
			{
				do
				{
					cout << "Warning: Enter integer degree within range 1-360" << endl;
					cin >> deg;
				} while (stoi(deg) < 20 || stoi(deg) > 500);
			}
			command = "ccw " + deg;
			if (drone.sendCommand(command))
			{
				cout << "Command 'counter clockwise' sent successfully" << endl;
			}
			else
			{
				cout << "Something went wrong!" << endl;
			}

			break;

		case 27:

			if (drone.land())
			{
				cout << "Drone landed successfully" << endl;
			}
			else
			{
				cout << "Something went wrong!" << endl;
			}

			goto end_main;

		default:

			cout << "Enter key from the menu to control drone: " << endl;
			cout << "Following are the keys to control the drone using the keyboard " << endl;
			cout << "Press: <key> followed by a distance value (in cm) to move the drone " << endl;
			cout << "[key - Up] x move forward 'x' cm" << "\n" << "[key - Down] x move back 'x' cm" << "\n"
				<< "[key - Left] x move left 'x' cm" << "\n" << "[key - Right] x move right 'x' cm" << "\n"
				<< "[key - w] x move up 20cm" << "\n" << "[key - s] x move down 'x' cm" << "\n"
				<< "[key - a] x rotate counter - clockwise by 'x' degree" << "\n"
				<< "[key - d] x rotate clockwise by 'x' degree" << "\n"
				<< "Esc to quit the control panel and land the drone " << endl;
		}

	}

	end_main:
		printf("Press any key to continue...\n");
		_getch();

	return 0;

}