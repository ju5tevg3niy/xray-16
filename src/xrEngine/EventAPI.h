#include "Common/types.hpp"
#pragma once

#include <vector>

#include "xrCore/Threading/Lock.hpp"
#include "Common/Noncopyable.hpp"

class CEvent;
typedef CEvent* EVENT;

//---------------------------------------------------------------------
class IEventReceiver
{
public:
    virtual void OnEvent(EVENT E, u64 P1, u64 P2) = 0;
};
//---------------------------------------------------------------------
class CEventAPI : private Noncopyable
{
    struct Deferred
    {
        EVENT E;
        u64 P1;
        u64 P2;
    };

private:
    std::vector<EVENT> Events;
    std::vector<Deferred> Events_Deferred;
    Lock CS;

public:
#ifdef CONFIG_PROFILE_LOCKS
    CEventAPI() : CS(MUTEX_PROFILE_ID(CEventAPI)) {}
#endif // CONFIG_PROFILE_LOCKS

    EVENT Create(const char* N);
    void Destroy(EVENT& E);

    EVENT Handler_Attach(const char* N, IEventReceiver* H);
    void Handler_Detach(EVENT& E, IEventReceiver* H);

    void Signal(EVENT E, u64 P1 = 0, u64 P2 = 0);
    void Signal(pcstr E, u64 P1 = 0, u64 P2 = 0);
    void Defer(EVENT E, u64 P1 = 0, u64 P2 = 0);
    void Defer(pcstr E, u64 P1 = 0, u64 P2 = 0);

    void OnFrame();
    void Dump();
    bool Peek(pcstr EName);

    void _destroy();
};
