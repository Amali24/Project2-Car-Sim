#include <string>
#include "ThomasCarHeader.h"
#include <iostream>
#include <iomanip>
using namespace std;


void accelerate(int &previousSpeed, int &currentSpeed, int delta) {
	// Move current speed to previous
	previousSpeed = currentSpeed;
	// Increase speed by given delta
	currentSpeed += delta;
}

void brake(int &previousSpeed, int &currentSpeed, int delta) {
	// Move current speed to previous
	previousSpeed = currentSpeed;

	// If current speed is >= the braking delta,
	if (currentSpeed >= delta) {
		// Decrement by delta
		currentSpeed -= delta;
	}
	else
		// Otherwise, the vehicle is stopped (speed = 0)
		currentSpeed = 0;
}

void cruise(int &previousSpeed, int currentSpeed) {
	// Store current speed in previous speed
	previousSpeed = currentSpeed;
}

void demo(int &previousSpeed, int &currentSpeed, int delta, int &state, double &intervalDistance, double &totalDistance, int timeInterval) {
	// Cruise thrice and output status for each
	for (int i = 0; i < 3; i++) {
		doAction('c', previousSpeed, currentSpeed, delta, state, intervalDistance, totalDistance, timeInterval);
		outputStatus('c', state, currentSpeed, intervalDistance, totalDistance);
	}
	// Brake thrice and output status for each
	for (int i = 0; i < 5; i++) {
		doAction('a', previousSpeed, currentSpeed, delta, state, intervalDistance, totalDistance, timeInterval);
		outputStatus('a', state, currentSpeed, intervalDistance, totalDistance);
	}
	// Cruise five times more while outputting statuses
	for (int i = 0; i < 5; i++) {
		doAction('c', previousSpeed, currentSpeed, delta, state, intervalDistance, totalDistance, timeInterval);
		outputStatus('a', state, currentSpeed, intervalDistance, totalDistance);
	}
	// Brake eight times, output statuses
	for (int i = 0; i < 8; i++) {
		doAction('b', previousSpeed, currentSpeed, delta, state, intervalDistance, totalDistance, timeInterval);
		outputStatus('a', state, currentSpeed, intervalDistance, totalDistance);
	}
}

void outputStatusHeader() {
	// prints header block:
	// Function        Current State        Current Speed      Interval Distance      Total feet (and miles) traveled
	cout
		<< right << setw(10) << "Function" << right << setw(16) << "Current State" << right << setw(15)
		<< "Current Speed" << right << setw(20) << "Interval Distance" << right << setw(33)
		<< "Total feet (and miles) traveled" << endl;
}

void outputStatus(char command, int state, int currentSpeed, double intervalDistance, double totalDistance) {
	// Find miles by dividing feet by 5280
	double distanceInMiles = totalDistance / 5280.0;

	// Print data to fill header block defined in outputStatusHeader()
	// Format data to fit screen more properly
	cout
		<< right << setw(10) << getCommandString(command) << right << setw(16) << getStatusText(state) << right << setw(15)
		<< currentSpeed << right << setw(20) << intervalDistance << right << setw(20)
		<< fixed << showpoint << setprecision(2) << totalDistance << "(" << distanceInMiles << ")" << endl;
}

string getStatusText(int currentState) {
	
	// Straightforward; returns string corresponding to enum
	
	switch (currentState) {
	case STOPPED: return "Stopped";
		break;
	case ACCELERATING: return "Accelerating";
		break;
	case CRUISING: return "Cruising";
		break;
	case BRAKING: return "Braking";
	default: return "ERROR: Invalid State";
	}
}

void showHelp() {
	// Print help menu (wysiwyg)
	cout
		<< "Supported commands:" << endl
		<< "                a              accelerate." << endl
		<< "                b              brake." << endl
		<< "                c              cruise." << endl
		<< "                d              demo." << endl
		<< "                e              change the speed delta." << endl
		<< "                h              print this help text." << endl
		<< "                i              change the time interval." << endl
		<< "                q              quit (end the program)." << endl;
}

char getCommand() {
	char x;
	cin >> x;	 cin.ignore(80, '\n'); // get first character and clear buffer of all else

	while (!(x == 'a' || x == 'b' || x == 'c' || x == 'd' || x == 'e' || x == 'h' || x == 'i' || x == 'q' ||
		x == 'A' || x == 'B' || x == 'C' || x == 'D' || x == 'E' || x == 'H' || x == 'I' || x == 'Q')) {
		// while not a valid command (case-insensitive)
		cout << "Please enter a valid command." << endl;
		cin >> x;	 cin.ignore(80, '\n'); // get new character and clear buffer of all else
	}
	return x; // return valid letter
}

string getCommandString(char c) {
	// returns string for command (note: lowercase falls through to upper to make commands
	// not case sensitive)
	switch (c) {
	case 'a':
	case 'A':
		return "Accelerate";
		break;
	case 'b':
	case 'B':
		return "Brake";
		break;
	case 'c':
	case 'C':
		return "Cruise";
		break;
	default:
		return "";
	}
}

void doAction(char command, int &previousSpeed, int &currentSpeed, int &delta, int &state, double &intervalDistance, double &totalDistance, int &timeInterval) {
	 
	// Switch on command to execute given command, update distance traveled, and change state
	// Uppercase falls through to prevent case sensitivity
	switch (command) {
	case 'a':
	case 'A':
		accelerate(previousSpeed, currentSpeed, delta);
		updateDistanceTraveled(previousSpeed, currentSpeed, intervalDistance, totalDistance, timeInterval);
		state = ACCELERATING;
		break;
	case 'b':
	case 'B':
		brake(previousSpeed, currentSpeed, delta);
		// If vehicle is not stopped after slowing, status is braking
		if (currentSpeed >= delta) state = BRAKING;
		// Otherwise, it is stopped
		else state = STOPPED;
		updateDistanceTraveled(previousSpeed, currentSpeed, intervalDistance, totalDistance, timeInterval);
		break;
	case 'c':
	case 'C':
		cruise(previousSpeed, currentSpeed);
		// If vehicle is in motion, it is cruising
		if (currentSpeed > 0) state = CRUISING;
		// If vehicle is stopped, it remains stopped
		else state = STOPPED;
		updateDistanceTraveled(previousSpeed, currentSpeed, intervalDistance, totalDistance, timeInterval);
		break;
	case 'd':
	case 'D':
		demo(previousSpeed, currentSpeed, delta, state, intervalDistance, totalDistance, timeInterval);
		break;
	case 'e':
	case 'E':
		changeDelta(delta);
		break;
	case 'h':
	case 'H':
		// Print help menu
		showHelp();
		break;
	case 'i':
	case 'I':
		changeInterval(timeInterval);
		break;
	case 'q':
	case 'Q':
		// Quit program
		system("pause");
		exit(0);
		break;
	default:
		cout << "Invalid Command\n";
	}
}

void updateDistanceTraveled(int previousSpeed, int currentSpeed, double &intervalFeetTraveled, double &totalFeetTraveled, int timeInterval) {
	// Average current and previous speeds for average speed over interval
	double averageSpeed = (double(previousSpeed) + double(currentSpeed)) / 2;
	// Convert MPH to FPS
	double averageSpeed_FeetPerSecond = averageSpeed * 5280.0 / 3600.0;
	// Interval feet calculation (d = vt)
	intervalFeetTraveled = averageSpeed_FeetPerSecond * timeInterval;
	// Increment total with interval
	totalFeetTraveled += intervalFeetTraveled;
}

void changeDelta(int &delta) {
	cout
		<< "Current delta = " << delta << " MPH" << endl
		<< "Please enter a new speed delta (in integer MPH): ";
	delta = getInt();
}

void changeInterval(int &interval) {
	cout
		<< "Current time interval = " << interval << " seconds" << endl
		<< "Please enter a new time interval (in integer seconds): ";
	interval = getInt();
}

double getNum() {
	double x;		// Holds user input and will be returned
	while (!(cin >> x)) { // While cin object is broken
		cin.clear();		cin.ignore(80, '\n'); // Clear it and remove evertything from buffer
		cout << "ERROR: PLEASE PROVIDE A NUMBER. TRY AGAIN: "; // And print error message
	}
	cin.ignore(80, '\n'); // Clear keyboard buffer
	return x;	// And return validated number
}

int getInt() {
	double x = getNum(); // validate input is number
	while (int(x) != x) { // while not int
		cout << "ERROR: INPUT MUST BE INTEGER. TRY AGAIN: "; // print error
		x = getNum(); // get new number
	}
	return int(x); // return valid int (typecasted to supress errors)
}