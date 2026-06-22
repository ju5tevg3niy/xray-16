#pragma once
#include "xrCore/Utils/fastdelegate.hpp"

namespace compression
{
namespace ppmd
{
class stream;
}
}

u32 ppmd_compress(
    void* dest_buffer, const u32& dest_buffer_size, const void* source_buffer, const u32& source_buffer_size);
u32 ppmd_trained_compress(void* dest_buffer, const u32& dest_buffer_size, const void* source_buffer,
    const u32& source_buffer_size, compression::ppmd::stream* tmodel);
u32 ppmd_decompress(
    void* dest_buffer, const u32& dest_buffer_size, const void* source_buffer, const u32& source_buffer_size);
u32 ppmd_trained_decompress(void* dest_buffer, const u32& dest_buffer_size, const void* source_buffer,
    const u32& source_buffer_size, compression::ppmd::stream* tmodel);

typedef fastdelegate::FastDelegate<void()> ppmd_yield_callback_t;
u32 ppmd_compress_mt(void* dest_buffer, const u32& dest_buffer_size, const void* source_buffer,
    const u32& source_buffer_size, ppmd_yield_callback_t ycb);
u32 ppmd_decompress_mt(void* dest_buffer, const u32& dest_buffer_size, const void* source_buffer,
    const u32& source_buffer_size, ppmd_yield_callback_t ycb);
