#pragma once

#include "Common/types.hpp"
#include "xrCore/FS.h"

void getFileCrc32(IReader* F, pcstr filePath, u32& outCrc, bool parseIncludes = true); // sets the value of outCrc
void addFileCrc32(IReader* F, pcstr filePath, u32& outCrc, bool parseIncludes = true); // just adds to outCrc
