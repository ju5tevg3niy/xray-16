#pragma once
#include <cstddef>
#include "Common/types.hpp"

inline void MemFill32(void* dst, u32 value, size_t dstSize) {
  u32* ptr = static_cast<u32*>(dst);
  u32* end = ptr + dstSize;
  while (ptr != end)
    *ptr++ = value;
}
