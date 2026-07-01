#pragma once
#include <string>
#include <vector>
#include "Common/Platform.hpp"  // IWYU pragma: keep
#include "Common/types.hpp"

std::vector<std::string> BuildStackTrace(u16 maxFramesCount = 512);

#ifdef XR_PLATFORM_WINDOWS
std::vector<std::string> BuildStackTrace(PCONTEXT threadCtx, u16 maxFramesCount);
#endif
