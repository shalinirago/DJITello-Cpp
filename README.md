# DJI Tello C++:

## Introduction

This repository consists of sample C++ code to interact with the Ryze Tello EDU Drone. This project works with Windows only.

## Description

The toolkit consists of two simple codes based on the Tello SDK written for the C++17 compiler using Microsoft Visual Studio 2019. Development for Tello has been done using various other programming languages such as Python, Go, Kotlin etc. and the set of APIs can be found [here](https://tellopilots.com/wiki/development/). Follow the [Tello SDk User Guide](https://dl-cdn.ryzerobotics.com/downloads/Tello/Tello%20SDK%202.0%20User%20Guide.pdf) for complete information about the drone and its functioning.

## Tello API

The TelloApi.h and TelloApi.cpp files consist of the Tello class that is responsible for communicating with the drone:

* Communication with the Tello is done using UDP at port 8889 and IP address '192.168.10.1'. 
* A windows socket is first created and validated
* The binding of the socket to the Tello IP address and port is done
* An asynchronous thread is initialised to continuously listen to the port
* In order to communicate with the drone using string commands, initially the drone is armed by sending "command"
* The string commands sent are converted to UTF-8 format

There are two projects written to control the drone: Control via the console and control by writing a set of commands in a .txt file and sending these commands to the drone. For both projects, download the code and open the .vcxproj file to open the Visual Studio project. Build the project to create the .exe file and run.

* **Tello control with console**

In this project, the Tello drone can be controlled using the console. A socket is initialised to communicate with the drone and using the keys on the keyboard, the drone can be maneuvered. User's input to control the speed of the drone when arming the drone is also essential. The command panel to control the drone is given below:

| Key     | Direction     | Range (to be entered)     |
|---------|---------------|---------------------------|
|key - Up | forward       | 20cm - 500 cm             |
|key - Down | back       | 20cm - 500 cm             |
|key - Right | right       | 20cm - 500 cm             |
|key - Left | left       | 20cm - 500 cm             |
|key - w | up       | 20cm - 500 cm             |
|key - s | down       | 20cm - 500 cm             |
|key - d | clockwise       | 1 - 360 deg             |
|key - s | counter-clockwise       | 1 - 360 deg             |
|Esc | quit control and land drone       |  |

* **Tello control using command.txt**

In this project, a series of commands can be designed into a .txt script for the tello to execute. The Tello's reference for these commands can be found in the Tello SDK user guide as released by DJI found [here](https://dl-cdn.ryzerobotics.com/downloads/Tello/Tello%20SDK%202.0%20User%20Guide.pdf)

Modify the command.txt file to include a range of commands including flips, curves, jump, etc. Ensure that the battery is full when attempting to send complex commands such as flips and curves to the drone.

## Troubleshooting

* Ensure that the firewall is off temporarily if a connection to the drone is not established
* Use [Wireshark](https://www.wireshark.org/) to analyze the UDP packets sent; this is an efficient tool to trace the packets sent out and to analyse the network
* If no connection is being made to the drone, update firmware of the Tello using the Tello EDU app



