#ifndef STACK_TRACK_H_GUARD_
#define STACK_TRACK_H_GUARD_

#include <chrono>
#include <memory>
#include <sstream>
#include <thread>
#include <unordered_map>

class IStringStreamLogger {
public:
  virtual void Log(const std::stringstream &) = 0;
};

class StringStreamLoggerToConsole : public IStringStreamLogger {
public:
  virtual void Log(const std::stringstream &) override;
};

class StringStreamLoggerToFile : public IStringStreamLogger {
public:
  virtual void Log(const std::stringstream &) override;
};

class StackTrackUserClass;

class StackTrack {
public:
  explicit StackTrack(const std::string &callerName,
                      const std::thread::id &threadId);
  ~StackTrack();

private:
  StackTrack(const StackTrack &) = delete;
  StackTrack &operator=(const StackTrack &) = delete;

  const std::thread::id mThread;
  const std::string mCallerName;
  static std::unordered_map<std::thread::id, unsigned int> mCount;
  static std::unordered_map<std::thread::id, std::stringstream> mLog;
  static std::unique_ptr<IStringStreamLogger> mLogger;
  std::chrono::time_point<std::chrono::high_resolution_clock> mStart;

private:
  void PrettifyStart();
  void PrettifyStop();
};

#endif