#include <kipr/wombat.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define INTERSECTION_TURN_LEFT 111
#define INTERSECTION_TURN_RIGHT 121
#define INTERSECTION_SKIP 131

////////////////////////
// CONSTANTS
////////////////////////
int THRESHOLD = 2207;
int SECOND_THRESHOLD = 2240;
int EDGE_THRESHOLD = 2207;
int EDGE_SECOND_THRESHOLD = 2190;

float INTERSECTION_EXTRA = 6.0; // distance on intersection
float ROTATE_SPEED = 45; // degrees per second
float DRIVE_SPEED = 0.5f; // centimeters per second

// Servo Constants
int TICK_DEGREE = 10;
int HOME_DEGREE = -315;

// Servo Presets
int UP_PRESET = 150;
int HOME_PRESET = 90;

int CLAW_PORT = 0;
int ARM_PORT = 1;

int CLOSE_CLAW = 250;
int OPEN_CLAW = 790;

int DEFAULT_DELAY = 1000;

int LONG_ARM_BUTTON = 0;


//////////////////////////
// FUNCTION DECLARATIONS
//////////////////////////
const char* color_check(const char* sensor);
void line_follow(int intersection, int duration, bool stopOnInt, int iterationsUntilStop);

void setArmAngle(int angle);
void openClaw();
void closeClaw();

void servoMove(int port, int position);
float cmToMeters(float length);

void original();

////////////////////////
// MAIN
////////////////////////
int main() {
	printf("Hello world\n");
    original();
    return 0;
}

void original()
{
    printf("Hello World\n");
    create3_connect();
    enable_servos();
    openClaw();

    setArmAngle(UP_PRESET);
    
    create3_drive_straight(cmToMeters(85), DRIVE_SPEED);
    create3_drive_straight(-cmToMeters(85), DRIVE_SPEED);
    create3_wait();
    
    printf("Cliff 1: %d\n",create3_sensor_cliff(0));
    printf("Cliff 2: %d\n",create3_sensor_cliff(3));

    create3_drive_straight(cmToMeters(30), DRIVE_SPEED);

    create3_rotate_degrees(50, ROTATE_SPEED);
    create3_drive_straight(cmToMeters(27), DRIVE_SPEED);
    create3_wait();

    printf("Starting line follow\n");

    line_follow(INTERSECTION_TURN_LEFT, 2500, true, 2);

    printf("Rotation complete, following second line\n");
    line_follow(INTERSECTION_SKIP, 250, false, 0);
    create3_wait();

    for (int i; i < 1800; i++) {
        create3_velocity_set_components(0, -0.3);
    } // little extra buffer

    printf("Move arm upwards\n");
    setArmAngle(UP_PRESET - 20);

    printf("Move 4 cm\n");
    create3_drive_straight(cmToMeters(2), DRIVE_SPEED);
    create3_wait();

    closeClaw();

    create3_drive_straight(-cmToMeters(25), DRIVE_SPEED);
    create3_wait();

    setArmAngle(UP_PRESET);
    return 0;
}

////////////////////////
// FUNCTION DEFINITIONS
////////////////////////
const char* color_check(const char* sensor) {
    if (strcmp(sensor, "left") == 0) {
        return (create3_sensor_cliff(1) > THRESHOLD ? "white" : "black");
    } else if (strcmp(sensor, "right") == 0) {
        return (create3_sensor_cliff(2) > SECOND_THRESHOLD ? "white" : "black");
    } else if (strcmp(sensor, "edge") == 0) {
        return (create3_sensor_cliff(0) > EDGE_THRESHOLD ? "white" : "black");
    } else if (strcmp(sensor, "edge2") == 0 ) {
        return (create3_sensor_cliff(3) > EDGE_SECOND_THRESHOLD ? "white" : "black");
    } else {
        printf("wtf???");
        return "wtf??";
    }
}

void line_follow(int intersection, int duration, bool stopOnInt, int iterationsUntilStop) {
    // if left is white and right is black: turn right
    // if left is white and right is white: go forward
    // if left is black and right is white: turn left
    // if black and black: go forward
    // intersection can have multiple values: TURN_LEFT, 

    int timer = 0;
    int stopIterations = 0;
    while (timer < duration)
    {
        bool leftSensIsWhite = strcmp(color_check("left"), "white") == 0;
        bool rightSensIsWhite = strcmp(color_check("right"), "white") == 0;

        bool leftEdge = strcmp(color_check("edge"), "black") == 0;
        bool rightEdge = strcmp(color_check("edge2"), "black") == 0;

        if (leftEdge || rightEdge) {
            if (intersection == INTERSECTION_SKIP) { continue; }
            create3_drive_straight(cmToMeters(INTERSECTION_EXTRA), 0.25);

            float rotAngle = (intersection == INTERSECTION_TURN_LEFT) ? 90 : -90;
            create3_rotate_degrees(rotAngle, ROTATE_SPEED);

            create3_wait();

            if (stopOnInt) { 
                stopIterations++; 
                if (stopIterations == stopOnInt); 
                return; 
            }   
            continue;
        }

        float turnSpeed;
        if (leftSensIsWhite == rightSensIsWhite) { turnSpeed = 0; }
        turnSpeed = (!leftSensIsWhite) ? 0.3 : -0.3;

        create3_velocity_set_components(0.1, turnSpeed);
        timer++;
    }
}

void setArmAngle(int angle)
{
    int angleTicks = HOME_DEGREE + (TICK_DEGREE * angle);

    set_servo_position(ARM_PORT, angleTicks);
    msleep(DEFAULT_DELAY);
}

void openClaw()
{
    set_servo_position(CLAW_PORT, OPEN_CLAW);
    msleep(DEFAULT_DELAY);
}

void closeClaw()
{
    set_servo_position(CLAW_PORT, CLOSE_CLAW);
    msleep(DEFAULT_DELAY);
}

// Claw Functions
void servoMove(int servo, int position)
{
    set_servo_position(servo, position);
}

// Helper Functions
float cmToMeters(float length)
{
    return (length / 100.0f);
}
