#include "Common/types_paths.hpp"
#include "Common/types.hpp"
#pragma once

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
