#include "StackTrack.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>  // This header is required for Windows-specific functions
#endif
void StringStreamLoggerToConsole::Log(const std::stringstream& ss)
{
#ifdef _WIN32
    // Set console output to UTF-8 code page
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::cout << ss.str();
}

void StringStreamLoggerToFile::Log(const std::stringstream& ss)
{
    // log to file here ...
}

// StackTrack
StackTrack::StackTrack(const std::string& callerName)
: mCallerName(callerName)
{
    if(mLogger == nullptr)
        mLogger = std::make_unique<StringStreamLoggerToConsole>();
    ++mCount;
    PrettifyStart();
    mLog << mCallerName << "::StackTrack START \n";
}

StackTrack::~StackTrack()
{
    PrettifyStop();
    mLog << mCallerName << "::StackTrack END \n";
    --mCount;
    if(mCount == 0)
        mLogger->Log(mLog);
}

unsigned int StackTrack::mCount = 0;
std::stringstream StackTrack::mLog;
std::unique_ptr<IStringStreamLogger> StackTrack::mLogger;


void StackTrack::PrettifyStart() // Adds an arrow "--->"
{
    if (mCount == 1)
    {
        mLog << "├─";
    }
    else
    {
        for (unsigned int i = 1; i < mCount; ++i)
            mLog << "│ ";
        mLog << "├─";
    }
}
void StackTrack::PrettifyStop() // Adds an arrow "<---"
{
    if (mCount == 1)
    {
        mLog << "├─";
    }
    else
    {
        for (unsigned int i = 1; i < mCount; ++i)
            mLog << "│ ";
        mLog << "├─";
    }

}