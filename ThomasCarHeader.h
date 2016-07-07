#ifndef CAR_H
#define CAR_H

#include <string>
using namespace std;

// Used to accelerate car
// Does not change state of car
// Alters current speed and previous speed by reference
void accelerate(int&, int&, int);

// Used to accelerate car
// Does not change state of car
// Alters current speed and previous speed by reference
void brake(int&, int&, int);

// Sets car to "cruise"
// Does not change state
// Alters current speed by reference
void cruise(int&, int);

// Shows demo
// Alters current speed, previous speed, state, distances traveled by reference
void demo(int&, int&, int, int&, double&, double&, int);
// Prints header
void outputStatusHeader();
// Prints current status (speed, state, distance)
void outputStatus(char, int, int, double, double);
// Returns string for state (based on enum State, defined below)
string getStatusText(int);
// Prints help menu
void showHelp();
// Gets valid command
char getCommand();
// Does the "action" (i.e. brake, accelerate, cruise)
void doAction(char, int&, int&, int&, int&, double&, double&, int&);
// Returns string for command given
string getCommandString(char);
// Updates total and interval distances traveled by reference
void updateDistanceTraveled(int, int, double&, double&, int);
// Allows user to update delta
void changeDelta(int&);
// Allows user to update interval time
void changeInterval(int&);
// Gets validated number
double getNum();
// Gets validated integer
int getInt();

// Used to track state of vehicle
enum State { STOPPED, ACCELERATING, BRAKING, CRUISING };
#endif