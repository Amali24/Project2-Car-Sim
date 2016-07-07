#include <iostream>
#include <string>
#include "ThomasCarHeader.h"
using namespace std;

int main(){
	char command;					// Holds single char for command
	int	delta = 5,					// Holds delta, changeable by user
		timeInterval = 1,			// Time interval (in seconds) - changeable by user
		currentState = STOPPED,		// Vehicle begins stopped
		previousSpeed,				// Previous speed (initialized to current speed at first action taken)
		currentSpeed = 0;			// Current speed of vehicle
	double totalFeetTraveled = 0,	// Total distance traveled, starts at zero
		intervalFeetTraveled = 0;	// Interval distance traveled, also starts at zero
	
	// Print header
	outputStatusHeader();
	
	while (true) {
		
		cout << "Command: ";	// Prompt user for command
		command = getCommand();	// Get the user's command
		// Execute user's command
		doAction(command, previousSpeed, currentSpeed, delta, currentState, intervalFeetTraveled, totalFeetTraveled, timeInterval);
		
		if (command == 'h' || command == 'H') {
			// Don't print status if help menu printed
		}

		// Alert user if they changed delta or interval (and display new delta/interval)
		else if (command == 'i' || command == 'I' || command == 'e' || command == 'E') {
			cout 
				<< ((command == 'i' || command == 'I') ? "Interval" : "Delta") << " updated successfully.\n"
				<< "New " << ((command == 'i' || command == 'I') ? "Interval" : "Delta") << " = " 
				<< ((command == 'i' || command == 'I') ? timeInterval : delta) << ".\n";
		}

		else {
			// Print status of vehicle if action taken
			outputStatus(command, currentState, currentSpeed, intervalFeetTraveled, totalFeetTraveled);
		}
	}
	return 0;
}