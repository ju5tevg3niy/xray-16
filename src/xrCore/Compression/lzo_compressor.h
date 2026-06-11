#pragma once

#include "xrCore/xrCore.h"

int lzo_compress_dict(
    const void* input, u32 inputSize, void* output, u32& outputSize, void* workMem, const void* dict, u32 dictSize);

int lzo_decompress_dict(
    const void* input, u32 inputSize, void* output, u32& outputSize, void* workMem, const void* dict, u32 dict_len);

int lzo_initialize();

u32 lzo_get_workmem_size();
