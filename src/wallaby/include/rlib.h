#ifndef R_LIB
#define R_LIB

#include <constants.h>
#include <kipr/wombat.h>
#include <math.h>

void setArmAngle(int angle);
void openClaw();
void closeClaw();

void clearPosCounters();

// Functions
void moveForward(int ticks);
void moveBackward(int ticks);
void turnRight(int ticks);
void turnLeft(int ticks);

void servoMove(int port, int position);

int cmToRev(float length);

#endif