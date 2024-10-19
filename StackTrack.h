#ifndef STACK_TRACK_H_GUARD_
#define STACK_TRACK_H_GUARD_

#include <sstream>
#include <memory>
#include <chrono>

class IStringStreamLogger
{
    public:
    virtual void Log(const std::stringstream&) = 0;
};

class StringStreamLoggerToConsole
: public IStringStreamLogger
{
    public:
    virtual void Log(const std::stringstream&) override;
};

class StringStreamLoggerToFile
: public IStringStreamLogger
{
    public:
    virtual void Log(const std::stringstream&) override;
};

class StackTrackUserClass;

class StackTrack
{   
    public:
    explicit StackTrack(const std::string& callerName);
    ~StackTrack();
    
    private:
    StackTrack(const StackTrack&) = delete;
    StackTrack& operator=(const StackTrack&) = delete;

    const std::string mCallerName;
    static unsigned int mCount;
    static std::stringstream mLog;
    static std::unique_ptr<IStringStreamLogger> mLogger;
    std::chrono::time_point<std::chrono::high_resolution_clock> mStart;

    private:
    void PrettifyStart();
    void PrettifyStop();
};

#endif