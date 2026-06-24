#pragma once

#include "xrCore/Math/matrix.hpp"
#include "xrsharedmem.h"
#include "xrstring.h"
#include "xr_resource.h"
#include "Compression/rt_compressor.h"
#include "xr_shared.h"
#include "string_concatenations.h"
#include "xrCore/Math/flags.hpp"

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
#include "Utils/fastdelegate.hpp"

#include "net_utils.h"
#include "xrCore/Threading/ThreadUtil.hpp"

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
