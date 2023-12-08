#include <rlib.h>

// settings...

int main()
{
    enable_servos();
    
    // Put arm in the air and open the claw
    setArmAngle(settings.UP_PRESET);
    openClaw();
    
    // Move forward to first cube
    moveForward(cmToRev(6));
    
    // Bring arm down, grab the cube, and bring arm up
    setArmAngle(settings.HOME_PRESET);
    closeClaw();
    setArmAngle(0);
    
    // turn left, move 3 cm, turn back
    turnLeft(settings.FULL_TURN);
    turnRight(settings.FULL_TURN);
    
    // move towards red cube
    moveForward(cmToRev(11));
    
    return 0;
}
