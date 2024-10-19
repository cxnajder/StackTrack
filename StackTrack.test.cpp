#include "StackTrack.macro.h"
#include <thread>
#include <chrono>

void artificialDelay()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void buzz()
{
    STACK_TRACK_THIS_FUNCTION
    artificialDelay();
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