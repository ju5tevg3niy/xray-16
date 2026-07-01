#include "xrCore/Threading/ScopeLock.hpp"
#include "xrCore/Threading/Lock.hpp"
#include "xrCore/xrDebug_macros.h"

ScopeLock::ScopeLock(Lock* SyncObject) : syncObject(SyncObject) {
  R_ASSERT(syncObject);
  syncObject->Enter();
}

ScopeLock::~ScopeLock() {
  syncObject->Leave();
}
