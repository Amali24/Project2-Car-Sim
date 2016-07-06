#include <string>
#include "ThomasCarHeader.h"
#include <iostream>
#include <iomanip>
using namespace std;


void accelerate(int &previousSpeed, int &currentSpeed, int delta) {
	previousSpeed = currentSpeed;
	currentSpeed += delta;
}

void brake(int &previousSpeed, int &currentSpeed, int delta) {
	previousSpeed = currentSpeed;
	if (currentSpeed > delta) {
		currentSpeed -= delta;
	}
	else
		currentSpeed = 0;
}

void cruise(int &previousSpeed, int currentSpeed) {
	previousSpeed = currentSpeed;
}

void outputStatusHeader() {
	cout
		<< right << setw(10) << "Function" << right << setw(16) << "Current State" << right << setw(15)
		<< "Current Speed" << right << setw(20) << "Interval Distance" << right << setw(33)
		<< "Total feet (and miles) traveled" << endl;
}

void outputStatus(int currentState) {

}

string getStatusText(int currentState) {
	switch (currentState) {
	case STOPPED: return "Stopped";
		break;
	case ACCELERATING: return "Accelerating";
		break;
	case CRUISING: return "Cruising";
		break;
	default: return "ERROR: Invalid State";
	}
}

void showHelp() {
	cout
		<< "Supported commands:" << endl
		<< "                a              accelerate." << endl
		<< "                b              brake." << endl
		<< "                c              cruise." << endl
		<< "                d              demo." << endl
		<< "                h              print this help text." << endl
		<< "                q              quit (end the program)." << endl;
}

char getCommand() {
	char x;
	cin >> x;	 cin.ignore(80, '\n'); // get first character and clear buffer of all else

	while (!(x == 'a' || x == 'b' || x == 'c' || x == 'd' || x == 'h' || x == 'q' ||
		x == 'A' || x == 'B' || x == 'C' || x == 'D' || x == 'H' || x == 'Q')) {
		// while not a valid command
		cout << "Please enter a valid command." << endl;
		cin >> x;	 cin.ignore(80, '\n'); // get new character and clear buffer of all else
	}
	return x; // return valid letter
}

void doAction(char command, int &previousSpeed, int &currentSpeed, int delta, int &state) {
	switch (command) {
	case 'a':
	case 'A':
		accelerate(previousSpeed, currentSpeed, delta);
		break;
	case 'b':
	case 'B':
		brake(previousSpeed, currentSpeed, delta);
		break;
	}
}