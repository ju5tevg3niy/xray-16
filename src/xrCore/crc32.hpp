#pragma once

#include "Common/types.hpp"

extern u32 crc32(const void* P, u32 len);

extern u32 crc32(const void* P, u32 len, u32 starting_crc);

// ignores '/' and '\'
extern u32 path_crc32(const char* path, u32 len);
