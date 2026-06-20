#pragma once

#define MACRO_TO_STRING_HELPER(a) #a
#define MACRO_TO_STRING(a) MACRO_TO_STRING_HELPER(a)

#define CONCATENIZE_HELPER(a, b) a##b
#define CONCATENIZE(a, b) CONCATENIZE_HELPER(a, b)

#include "xrDebug.h"
#include "xrMemory.h"

//#include "_stl_extensions.h"
#include "xrCore/Math/rect.hpp"
#include "xrCore/Math/matrix.hpp"
#include "xrsharedmem.h"
#include "xrstring.h"
#include "xr_resource.h"
#include "Compression/rt_compressor.h"
#include "xr_shared.h"
#include "string_concatenations.h"
#include "xrCore/Math/flags.hpp"

// stl ext
struct xr_rtoken
{
    shared_str name;
    int id;

    xr_rtoken(pcstr _nm, int _id)
        : name(_nm), id(_id) {}

    void rename(pcstr _nm) { name = _nm; }
    bool equal(pcstr _nm) const { return (0 == xr_strcmp(name.c_str(), _nm)); }
};

#include "xr_shortcut.h"

#include "FS.h"
#include "log.h"
#include "xr_trims.h"
#include "xr_ini.h"
#ifdef NO_FS_SCAN
#include "ELocatorAPI.h"
#else
#include "LocatorAPI.h"
#endif
#include "FileSystem.h"
#include "FTimer.h"
#include "fastdelegate.h"
#ifdef XR_PLATFORM_WINDOWS
#include "intrusive_ptr.h"
#endif

#include "net_utils.h"
#include "xrCore/Threading/ThreadUtil.hpp"

// destructor
template <class T>
class destructor
{
    T* ptr;

public:
    destructor(T* p) { ptr = p; }
    ~destructor() { xr_delete(ptr); }
    T& operator()() { return *ptr; }
};

// ***** The Core definition *****
class xrCore
{
    u32 buildId;
    static const pcstr buildDate;
    static const pcstr buildCommit;
    static const pcstr buildBranch;

public:
    xrCore();

    string64 ApplicationName;
    string64 ApplicationTitle;
    string_path ApplicationPath;
    string_path WorkingPath;
    string64 UserName;
    string64 CompName;
    char* Params;
    u32 dwFrame;
    bool PluginMode;

    void Initialize(
        pcstr ApplicationName, pcstr commandLine = nullptr, bool init_fs = true, pcstr fs_fname = nullptr, bool plugin = false);
    void _destroy();

    u32 GetBuildId() const { return buildId; }
    static pcstr GetBuildDate() { return buildDate; }
    static pcstr GetBuildCommit() { return buildCommit; }
    static pcstr GetBuildBranch() { return buildBranch; }

private:
    void CalculateBuildId();
    void PrintBuildInfo();
};

extern xrCore Core;
