#pragma once
#include "Common/types.hpp"
#include "xrCore/FS.h"

// sets the value of outCrc
void getFileCrc32(IReader* F,
                  pcstr filePath,
                  u32& outCrc,
                  bool parseIncludes = true);

// just adds to outCrc
void addFileCrc32(IReader* F,
                  pcstr filePath,
                  u32& outCrc,
                  bool parseIncludes = true);
