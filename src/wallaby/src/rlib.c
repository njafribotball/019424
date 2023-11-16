#include <rlib.h>

extern CONSTANT_SETTINGS settings;

void clearPosCounters()
{
    cmpc(0); cmpc(1);
}

// Servo Functions

void setArmAngle(int angle)
{
    int angleTicks = settings.HOME_DEGREE - (settings.TICK_DEGREE * angle);
    
    set_servo_position(settings.ARM_PORT, angleTicks);
    msleep(settings.DEFAULT_DELAY);
}

void openClaw()
{
    set_servo_position(settings.CLAW_PORT, settings.OPEN_CLAW);
    msleep(settings.DEFAULT_DELAY);
}

void closeClaw()
{
 	set_servo_position(settings.CLAW_PORT, settings.CLOSE_CLAW);
    msleep(settings.DEFAULT_DELAY);
}


// Motor Functions
void moveForward(int ticks)
{
    if (settings.LOGGING) printf("Moving Forward...\n");
    clearPosCounters();
    while (gmpc(settings.LEFT_MOTOR) < ticks) {
        motor(settings.LEFT_MOTOR, settings.LEFT_MOTOR_SPEED);
        motor(settings.RIGHT_MOTOR, settings.RIGHT_MOTOR_SPEED);
    };
    ao();
}

void moveBackward(int ticks)
{
    if (settings.LOGGING) printf("Moving Backward...\n");
    clearPosCounters();
    while (gmpc(settings.LEFT_MOTOR) > ticks) {
        motor(settings.LEFT_MOTOR, -settings.LEFT_MOTOR_SPEED);
        motor(settings.RIGHT_MOTOR, -settings.RIGHT_MOTOR_SPEED);
    };
    ao();
}

void turnRight(int ticks)
{
    if (settings.LOGGING) printf("Turning Right...\n");
    clearPosCounters();
    while (gmpc(settings.LEFT_MOTOR) < ticks) {
        motor(settings.LEFT_MOTOR, settings.LEFT_MOTOR_SPEED);
    };
    ao();
}

void turnLeft(int ticks)
{
    if (settings.LOGGING) printf("Turning left...\n");
    clearPosCounters();
    while (gmpc(settings.RIGHT_MOTOR) < ticks) {
        motor(settings.RIGHT_MOTOR, settings.RIGHT_MOTOR_SPEED);
    };
    ao();
}

// Claw Functions
void servoMove(int servo, int position)
{
    set_servo_position(servo, position);
}

// Helper Functions
int cmToRev(float length)
{
    return ((length / settings.FULL_REVOLUTION_CENTIMETERS) * 2200.0f);
}