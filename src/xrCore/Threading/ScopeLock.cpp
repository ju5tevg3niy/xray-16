#include "xrCore/xrDebug_macros.h"

#include "Lock.hpp"
#include "ScopeLock.hpp"

ScopeLock::ScopeLock(Lock* SyncObject) : syncObject(SyncObject) {
  R_ASSERT(syncObject);
  syncObject->Enter();
}

ScopeLock::~ScopeLock() {
  syncObject->Leave();
}
