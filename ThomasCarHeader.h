#ifndef CAR_H
#define CAR_H

#include <string>
using namespace std;

void accelerate(int&, int&, int);
void brake(int&, int&, int);
void cruise(int &, int);
void outputStatusHeader();
void outputStatus(int);
string getStatusText(int);
void showHelp();
char getCommand();
void doAction(char, int&, int&, int, int);

enum State { STOPPED, ACCELERATING, CRUISING };

#endif