#include "xrMemory.h"
#include <SDL.h>
#include <cstddef>
#include <cstdlib>
#include <new>
#include "Common/Platform.hpp"
#include "Common/types.hpp"
#include "Text/string_funcs_inline.hpp"
#include "xrDebug_macros.h"
#include "xrsharedmem.h"
#include "xrstring.h"
#if defined(XR_PLATFORM_WINDOWS)
#include <Psapi.h>
#elif defined(XR_PLATFORM_LINUX)
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sys/resource.h>
#elif defined(XR_PLATFORM_BSD)
#include <sys/time.h>
#include <sys/resource.h>
#elif defined(XR_PLATFORM_HAIKU)
#include <OS.h>
#include <sys/time.h>
#include <sys/resource.h>
#endif

// Additional bytes of memory to hide memory problems on Release
// But for Debug we don't need this if we want to find these problems
#ifdef NDEBUG
    constexpr size_t xr_reserved_tail = 8;
#else
    constexpr size_t xr_reserved_tail = 0;
#endif

#define xr_internal_malloc(size) malloc(size + xr_reserved_tail)
#define xr_internal_malloc_aligned(size, alignment) malloc(size + xr_reserved_tail)
#define xr_internal_malloc_nothrow(size) malloc(size + xr_reserved_tail)
#define xr_internal_malloc_nothrow_aligned(size, alignment) malloc(size + xr_reserved_tail)
#define xr_internal_small_alloc(size) malloc(size + xr_reserved_tail)
#define xr_internal_small_free(ptr) free(ptr)

#define xr_internal_realloc(ptr, size) realloc(ptr, size + xr_reserved_tail)
#define xr_internal_realloc_aligned(ptr, size, alignment) realloc(ptr, size + xr_reserved_tail)

#define xr_internal_free(ptr) free(ptr)
#define xr_internal_free_size(ptr, size) free(ptr)
#define xr_internal_free_aligned(ptr, alignment) free(ptr)
#define xr_internal_free_size_aligned(ptr, size, alignment) free(ptr)

xrMemory Memory;

void xrMemory::mem_compact()
{
#if defined(XR_PLATFORM_WINDOWS)
    RegFlushKey(HKEY_CLASSES_ROOT);
    RegFlushKey(HKEY_CURRENT_USER);
#endif

    /*
    Следующая команда, в целом, не нужна.
    Современные аллокаторы достаточно грамотно и когда нужно возвращают память операционной системе.
    Эта строчка нужна, скорее всего, в определённых ситуациях, вроде использования файлов отображаемых в память,
    которые требуют большие свободные области памяти.
    */
    //HeapCompact(GetProcessHeap(), 0);
    if (g_pStringContainer)
        g_pStringContainer->clean();
    if (g_pSharedMemoryContainer)
        g_pSharedMemoryContainer->clean();

#if defined(XR_PLATFORM_WINDOWS)
    if (strstr(Core.Params, "-swap_on_compact"))
        SetProcessWorkingSetSize(GetCurrentProcess(), size_t(-1), size_t(-1));
#endif
}

void* xrMemory::mem_alloc(size_t size)
{
    const auto result = xr_internal_malloc(size);
    //TracyAlloc(result, size);
    return result;
}

void* xrMemory::mem_alloc(size_t size, size_t alignment)
{
    const auto result = xr_internal_malloc_aligned(size, alignment);
    //TracyAlloc(result, size);
    return result;
}

void* xrMemory::mem_alloc(size_t size, const std::nothrow_t&) noexcept
{
    const auto result = xr_internal_malloc_nothrow(size);
    //TracyAlloc(result, size);
    return result;
}

void* xrMemory::mem_alloc(size_t size, size_t alignment, const std::nothrow_t&) noexcept
{
    const auto result = xr_internal_malloc_nothrow_aligned(size, alignment);
    //TracyAlloc(result, size);
    return result;
}

void* xrMemory::small_alloc(size_t size) noexcept
{
    const auto result = xr_internal_small_alloc(size);
    //TracyAllocN(result, size, "small alloc");
    return result;
}

void xrMemory::small_free(void* ptr) noexcept
{
    //TracyFree(ptr);
    xr_internal_small_free(ptr);
}

void* xrMemory::mem_realloc(void* ptr, size_t size)
{
    //TracyFree(ptr);
    const auto result = xr_internal_realloc(ptr, size);
    //TracyAllocN(result, size, "realloc");
    return result;
}

void* xrMemory::mem_realloc(void* ptr, size_t size, size_t alignment)
{
    //TracyFree(ptr);
    const auto result = xr_internal_realloc_aligned(ptr, size, alignment);
    //TracyAllocN(result, size, "realloc");
    return result;
}

void xrMemory::mem_free(void* ptr)
{
    //TracyFree(ptr);
    xr_internal_free(ptr);
}

void xrMemory::mem_free(void* ptr, size_t alignment)
{
    //TracyFree(ptr);
    xr_internal_free_aligned(ptr, alignment);
}

pstr xr_strdup(pcstr string)
{
    VERIFY(string);
    size_t len = strlen(string) + 1;
    auto memory = static_cast<char*>(xr_malloc(len));
    CopyMemory(memory, string, len);
    return memory;
}

[[nodiscard]] void* operator new(size_t size)
{
    return Memory.mem_alloc(size);
}

[[nodiscard]] void* operator new[](size_t size)
{
    return Memory.mem_alloc(size);
}

[[nodiscard]] void* operator new(size_t size, const std::nothrow_t&) noexcept
{
    return Memory.mem_alloc(size);
}

[[nodiscard]] void* operator new[](size_t size, const std::nothrow_t&) noexcept
{
    return Memory.mem_alloc(size);
}

[[nodiscard]] void* operator new(size_t size, std::align_val_t alignment)
{
    return Memory.mem_alloc(size, static_cast<size_t>(alignment));
}

[[nodiscard]] void* operator new[](size_t size, std::align_val_t alignment)
{
    return Memory.mem_alloc(size, static_cast<size_t>(alignment));
}

[[nodiscard]] void* operator new(size_t size, std::align_val_t alignment, const std::nothrow_t&) noexcept
{
    return Memory.mem_alloc(size, static_cast<size_t>(alignment));
}

[[nodiscard]] void* operator new[](size_t size, std::align_val_t alignment, const std::nothrow_t&) noexcept
{
    return Memory.mem_alloc(size, static_cast<size_t>(alignment));
}

void operator delete(void* ptr) noexcept
{
    Memory.mem_free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    Memory.mem_free(ptr);
}

void operator delete(void* ptr, std::align_val_t alignment) noexcept
{
    Memory.mem_free(ptr, static_cast<size_t>(alignment));
}

void operator delete[](void* ptr, std::align_val_t alignment) noexcept
{
    Memory.mem_free(ptr, static_cast<size_t>(alignment));
}

void operator delete(void* ptr, size_t) noexcept
{
    Memory.mem_free(ptr);
}

void operator delete[](void* ptr, size_t) noexcept
{
    Memory.mem_free(ptr);
}

void operator delete(void* ptr, size_t, std::align_val_t alignment) noexcept
{
    Memory.mem_free(ptr, static_cast<size_t>(alignment));
}

void operator delete[](void* ptr, size_t, std::align_val_t alignment) noexcept
{
    Memory.mem_free(ptr, static_cast<size_t>(alignment));
}

void* xr_malloc(size_t size)
{
    return Memory.mem_alloc(size);
}

void* xr_realloc(void* ptr, size_t size)
{
    return Memory.mem_realloc(ptr, size);
}
