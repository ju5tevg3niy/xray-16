#pragma once

#include "xrCommon/xr_vector.h"
#include "xrCommon/xr_string.h"

// fwd. decl.
template <class T> struct _vector3; typedef _vector3<float> Fvector;
struct Fmatrix;

#define VPUSH(a) ((a).x), ((a).y), ((a).z)

void __cdecl Msg(pcstr format, ...);

void Log(pcstr msg);
void Log(pcstr msg, pcstr dop);
void Log(pcstr msg, int dop);
void Log(pcstr msg, unsigned int dop);
void Log(pcstr msg, long dop);
void Log(pcstr msg, unsigned long dop);
void Log(pcstr msg, long long dop);
void Log(pcstr msg, unsigned long long dop);
void Log(pcstr msg, float dop);
void Log(pcstr msg, const Fvector& dop);
void Log(pcstr msg, const Fmatrix& dop);

void LogWinErr(pcstr msg, long err_code);

struct LogCallback
{
    typedef void (*Func)(void* context, const char* s);
    Func Log;
    void* Context;

    LogCallback() : Log(nullptr), Context(nullptr) {}
    LogCallback(std::nullptr_t) : Log(nullptr), Context(nullptr) {}
    LogCallback(Func log, void* ctx) : Log(log), Context(ctx) {}
    void operator()(const char* s) { Log(Context, s); }
    operator bool() const { return !!Log; }
};

LogCallback SetLogCB(const LogCallback& cb);
void CreateLog(bool no_log = false);
void InitLog();
void CloseLog();
void FlushLog();

extern xr_vector<xr_string> LogFile;
extern bool LogExecCB;
