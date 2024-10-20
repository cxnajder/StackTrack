#include "StackTrack.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif
void StringStreamLoggerToConsole::Log(const std::stringstream &ss) {
#ifdef _WIN32
  // Set console output to UTF-8 code page
  SetConsoleOutputCP(CP_UTF8);
#endif
  std::cout << ss.str();
}

void StringStreamLoggerToFile::Log(const std::stringstream &ss) {
  // log to file here ...
}

// StackTrack
StackTrack::StackTrack(const std::string &callerName,
                       const std::thread::id &threadId)
    : mCallerName(callerName), mThread(threadId) {
  if (auto search = mCount.find(mThread); search == mCount.end()) {
    mCount.insert({mThread, 0});
    mLog.insert({mThread, std::stringstream()});
  }
  if (mCount.at(mThread) == 0) {
    mLog.at(mThread) << "StackTrack::" << mThread << "::start \n";
  }
  if (mLogger == nullptr) {
    mLogger = std::make_unique<StringStreamLoggerToConsole>();
  }
  ++mCount.at(mThread);
  PrettifyStart();
  mLog.at(mThread) << mCallerName << "::start \n";
  mStart = std::chrono::high_resolution_clock::now();
}

StackTrack::~StackTrack() {
  std::chrono::duration<float> dur =
      std::chrono::high_resolution_clock::now() - mStart;
  float ms = dur.count() * 1000.0f;
  PrettifyStop();
  mLog.at(mThread) << mCallerName << "::stop ";
  mLog.at(mThread) << "- " << ms << "ms \n";
  --mCount.at(mThread);
  if (mCount.at(mThread) == 0) {
    mLog.at(mThread) << "StackTrack::" << mThread << "::stop \n";

    // might need a mutex/lockGuard here!
    mLogger->Log(mLog.at(mThread));
  }
}
std::unordered_map<std::thread::id, unsigned int> StackTrack::mCount;
std::unordered_map<std::thread::id, std::stringstream> StackTrack::mLog;
std::unique_ptr<IStringStreamLogger> StackTrack::mLogger;

void StackTrack::PrettifyStart()
{
  if (mCount.at(mThread) == 1) {
    mLog.at(mThread) << "├─";
  } else {
    for (unsigned int i = 1; i < mCount.at(mThread); ++i)
      mLog.at(mThread) << "│ ";
    mLog.at(mThread) << "├─";
  }
}
void StackTrack::PrettifyStop()
{
  if (mCount.at(mThread) == 1) {
    mLog.at(mThread) << "├─";
  } else {
    for (unsigned int i = 1; i < mCount.at(mThread); ++i)
      mLog.at(mThread) << "│ ";
    mLog.at(mThread) << "├─";
  }
}