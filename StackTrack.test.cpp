#include <iostream>

#include "StackTrack.macro.h"

void buzz()
{
    STACK_TRACK_THIS_FUNCTION
}

void bar()
{
    STACK_TRACK_THIS_FUNCTION
    buzz();
}

void foo()
{
    STACK_TRACK_THIS_FUNCTION
    bar(); 
}

int main()
{
    STACK_TRACK_THIS_FUNCTION
    foo();
    bar();
    buzz();
    foo();
}