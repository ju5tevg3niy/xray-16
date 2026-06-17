#include "xrCore/xrDebug_macros.h"

#include "ScopeLock.hpp"
#include "Lock.hpp"

ScopeLock::ScopeLock(Lock* SyncObject) : syncObject(SyncObject)
{
    R_ASSERT(syncObject);
    syncObject->Enter();
}

ScopeLock::~ScopeLock()
{
    syncObject->Leave();
}
