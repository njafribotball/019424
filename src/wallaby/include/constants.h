#ifndef R_CONSTANTS
#define R_CONSTANTS

#include <stdbool.h>

typedef struct CONSTANT_SETTINGS
{
    // Constants
    int LEFT_MOTOR;// = 0;
    int RIGHT_MOTOR;// = 1;

    int LEFT_MOTOR_SPEED;// = 50;
    int RIGHT_MOTOR_SPEED;// = 49;

    bool LOGGING;// = true;

    // Move Presets
    // A full revolution is approximately 1900 ticks, 90 degree turn is around a fourth more.
    // One full revolution move 22 centimeters.
    int FULL_TURN;// = 2400;
    float FULL_REVOLUTION_CENTIMETERS;// = 22;

    int TICK_DEGREE;// = 10;
    int HOME_DEGREE;// = 2040;

    int UP_PRESET;// = 40;
    int HOME_PRESET;// = 90;

    int CLAW_PORT;// = 1;
    int ARM_PORT;// = 2;

    int CLOSE_CLAW;// = 1790;
    int OPEN_CLAW;// = 1460;

    int DEFAULT_DELAY;// = 600;

} CONSTANT_SETTINGS;

// CONSTANT_SETTINGS defaultSettings = {
//     .LEFT_MOTOR = 0,
//     .RIGHT_MOTOR = 1,
// 
//     .LEFT_MOTOR_SPEED = 50,
//     .RIGHT_MOTOR_SPEED = 49,
// 
//     .LOGGING = true,

//     .FULL_TURN = 2400,
//     .FULL_REVOLUTION_CENTIMETERS = 22
// };

#endif