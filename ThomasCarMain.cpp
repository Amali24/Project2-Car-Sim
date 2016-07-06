#include <iostream>
#include <string>
#include "ThomasCarHeader.h"
using namespace std;

int main(){
	const int LINES_PER_SCREEN = 20;
	char command;
	int delta = 5, timesThru = 0, timeInterval = 1;
	int currentState, previousSpeed, currentSpeed;
	double averageSpeedMPH, averageSpeedFPS, totalFeetTraveled, intervalFeetTraveled;

	while (true) {
		if (timesThru % LINES_PER_SCREEN == 0) {
			system("cls");
			outputStatusHeader();
			timesThru++;
		}
		cout << "Command: ";
		command = getCommand();
		doAction(command);
	}

	system("pause");
	return 0;
}