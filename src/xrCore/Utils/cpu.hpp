#pragma once
#include "Common/types.hpp"

namespace CPU
{
extern bool HasSSE;
extern bool HasSSE2;
extern bool HasSSE42;
extern bool HasAVX;
extern bool HasAVX2;
extern bool HasAVX512F;

extern u64 qpc_freq;
extern u32 qpc_counter;

extern u64 QPC() noexcept;

u32 GetTicks();
}

extern void _initialize_cpu();
extern void _initialize_cpu_thread();
