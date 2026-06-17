#pragma once

#include "Common/Noncopyable.hpp"

class Lock;

class ScopeLock : Noncopyable {
  Lock* syncObject;

 public:
  ScopeLock(Lock* SyncObject);
  ~ScopeLock();
};
