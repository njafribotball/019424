#include <rlib.h>

// every 100 ticks is 10 degrees less
// so ever 10 ticks is one degree
// Theoretically 2040 ticks is zero degrees, DO NOT GO TO HOME DEGREE EVER, WILL BREAK CLAW

CONSTANT_SETTINGS settings = {
    .LEFT_MOTOR = 0,
    .RIGHT_MOTOR = 1,
 
    .LEFT_MOTOR_SPEED = 50,
    .RIGHT_MOTOR_SPEED = 49,
 
    .LOGGING = true,
 
    .FULL_TURN = 2400,
    .FULL_REVOLUTION_CENTIMETERS = 22,
    
    .TICK_DEGREE = 10,
    .HOME_DEGREE = 2040,

    .UP_PRESET = 40,
    .HOME_PRESET = 90,

    .CLAW_PORT = 1,
    .ARM_PORT = 2,

    .CLOSE_CLAW = 1790,
    .OPEN_CLAW = 1460,

    .DEFAULT_DELAY = 600
};

int main()
{
    enable_servos();
    setArmAngle(settings.UP_PRESET);
    openClaw();
    
    moveForward(cmToRev(14));
    setArmAngle(110);
    
    closeClaw();
    
    
    return 0;
}
