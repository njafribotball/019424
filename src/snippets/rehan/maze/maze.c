#include <rlib.h>

# settings...

int main()
{
    moveForward(cmToRev(21.0f));
    turnRight(settings.FULL_TURN);
    
    moveForward(cmToRev(15.0f));
    turnLeft(settings.FULL_TURN);

    moveForward(cmToRev(5.0f));
    turnLeft(settings.FULL_TURN);

    moveForward(cmToRev(15.0f));
    turnRight(settings.FULL_TURN);

    moveForward(cmToRev(3.0f));
    turnRight(settings.FULL_TURN);
    
    moveForward(cmToRev(15.0f));
    turnLeft(settings.FULL_TURN);

    moveForward(cmToRev(5.0f));
    turnLeft(settings.FULL_TURN);

    moveForward(cmToRev(13.0f));
    turnRight(settings.FULL_TURN);

    moveForward(cmToRev(3.0f));
    turnRight(settings.FULL_TURN);
    
    moveForward(cmToRev(5.0f));

    return 0;
}

