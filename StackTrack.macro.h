#ifndef STACK_TRACK_MACRO_H_GUARD_
#define STACK_TRACK_MACRO_H_GUARD_

#include "StackTrack.h"

#define STACK_TRACK_THIS_FUNCTION StackTrack st{__FUNCTION__, std::this_thread::get_id()};
//#define STACH_TRACK_WITH_CUSTOM_NAME()
//#define STACK_TRACK_SWITCH_LOGER
//#define STACK_TRACK_FLUSH_LOG_HERE

#endif