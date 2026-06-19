#pragma once

#include <string>
#include <cstddef>

#include "Common/Platform.hpp"
#include "Common/types.hpp"
#include "Common/types_paths.hpp"
#include "xrCommon/xr_smart_pointers.h"

#define BACKUP_FILE_LEVEL 5

class EFS_Utils
{
protected:
    bool GetOpenNameInternal(
        pcstr initial, pstr buffer, size_t sz_buf, bool bMulti = false, pcstr offset = 0, int start_flt_ext = -1);

public:
    void _initialize() {}
    void _destroy() {}
    pcstr GenerateName(pcstr base_path, pcstr base_name, pcstr def_ext, pstr out_name, size_t const out_name_size);

    bool GetOpenName(pcstr initial, string_path& buffer, int sz_buf, bool bMulti = false, pcstr offset = 0,
        int start_flt_ext = -1);
    bool GetOpenName(pcstr initial, std::string& buf, bool bMulti = false, pcstr offset = 0, int start_flt_ext = -1);

    bool GetSaveName(pcstr initial, string_path& buffer, pcstr offset = 0, int start_flt_ext = -1);
    bool GetSaveName(pcstr initial, std::string& buf, pcstr offset = 0, int start_flt_ext = -1);

    void MarkFile(pcstr fn, bool bDeleteSource);

    std::string AppendFolderToName(std::string& tex_name, int depth, BOOL full_name);

    pcstr AppendFolderToName(pstr tex_name, size_t const tex_name_size, int depth, BOOL full_name);
    pcstr AppendFolderToName(pcstr src_name, pstr dest_name, size_t const dest_name_size, int depth, BOOL full_name);

    std::string ChangeFileExt(pcstr src, pcstr ext);
    std::string ChangeFileExt(const std::string& src, pcstr ext);

    static std::string ExtractFileName(pcstr src);
    static std::string ExtractFilePath(pcstr src);
    static std::string ExtractFileExt(pcstr src);
    static std::string ExcludeBasePath(pcstr full_path, pcstr excl_path);
};

extern xr_unique_ptr<EFS_Utils> xr_EFS;

#define EFS (*xr_EFS)
