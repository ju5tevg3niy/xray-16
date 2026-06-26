#pragma once
#include <set>
#include <ctime>
#include <string>
#include "Common/types.hpp"
#include "Common/types_paths.hpp"
#include "xrCore/Math/flags.hpp"
#include "xrCore/xrstring.h"

enum FS_List : u32
{
    FS_ListFiles = (1 << 0),
    FS_ListFolders = (1 << 1),
    FS_ClampExt = (1 << 2),
    FS_RootOnly = (1 << 3),
};

class FS_Path
{
public:
    enum
    {
        flRecurse = (1 << 0),
        flNotif = (1 << 1),
        flNeedRescan = (1 << 2),
    };

public:
    pstr m_Path;
    pstr m_Root;
    pstr m_Add;
    pstr m_DefExt;
    pstr m_FilterCaption;
    Flags32 m_Flags;

public:
    FS_Path(pcstr _Root, pcstr _Add, pcstr _DefExt = 0, pcstr _FilterString = 0, u32 flags = 0);
    ~FS_Path();
    pcstr _update(string_path& dest, pcstr src) const;
    void _set(pcstr add);
    void _set_root(pcstr root);

    void rescan_path_cb();
};

struct _finddata64i32_t;
#define _FINDDATA_T _finddata64i32_t

struct FS_File
{
    enum
    {
        flSubDir = (1 << 0),
        flVFS = (1 << 1),
    };
    unsigned attrib;
    time_t time_write;
    long size;
    std::string name; // low-case name
    void set(const std::string& nm, long sz, time_t modif, unsigned attr);

public:
    FS_File() : attrib(0), time_write(0), size(0) {}
    FS_File(const std::string& nm);
    FS_File(const _FINDDATA_T& f);
    FS_File(const std::string& nm, const _FINDDATA_T& f);
    FS_File(const std::string& nm, long sz, time_t modif, unsigned attr);
    bool operator<(const FS_File& other) const { return xr_strcmp(name.c_str(), other.name.c_str()) < 0; }
};
using FS_FileSet = std::set<FS_File>;

extern bool PatternMatch(pcstr s, pcstr mask);
