#include "xrCore/xrMemory.h"
#include <SDL.h>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <new>
#include "Common/Platform.hpp"  // IWYU pragma: keep
#include "Common/types.hpp"
#include "xrCore/Memory/memory_funcs_inline.hpp"
#include "xrCore/xrDebug_macros.h"
#include "xrCore/xrsharedmem.h"
#include "xrCore/xrstring.h"
#if defined(XR_PLATFORM_WINDOWS)
#include <Psapi.h>
#elif defined(XR_PLATFORM_LINUX)
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#elif defined(XR_PLATFORM_BSD)
#include <sys/resource.h>
#include <sys/time.h>
#elif defined(XR_PLATFORM_HAIKU)
#include <OS.h>
#include <sys/resource.h>
#include <sys/time.h>
#endif

// Additional bytes of memory to hide memory problems on Release
// But for Debug we don't need this if we want to find these problems
#ifdef NDEBUG
constexpr size_t xr_reserved_tail = 8;
#else
constexpr size_t xr_reserved_tail = 0;
#endif

xrMemory Memory;

void xrMemory::mem_compact() {
#if defined(XR_PLATFORM_WINDOWS)
  RegFlushKey(HKEY_CLASSES_ROOT);
  RegFlushKey(HKEY_CURRENT_USER);
#endif

  /*
  Следующая команда, в целом, не нужна.
  Современные аллокаторы достаточно грамотно и когда нужно возвращают память
  операционной системе. Эта строчка нужна, скорее всего, в определённых
  ситуациях, вроде использования файлов отображаемых в память, которые требуют
  большие свободные области памяти.
  */
  // HeapCompact(GetProcessHeap(), 0);
  if (g_pStringContainer)
    g_pStringContainer->clean();
  if (g_pSharedMemoryContainer)
    g_pSharedMemoryContainer->clean();

#if defined(XR_PLATFORM_WINDOWS)
  if (strstr(Core.Params, "-swap_on_compact"))
    SetProcessWorkingSetSize(GetCurrentProcess(), size_t(-1), size_t(-1));
#endif
}

void* xrMemory::mem_alloc(size_t size) {
  return malloc(size + xr_reserved_tail);
}

void* xrMemory::mem_alloc(size_t size, size_t alignment) {
  return malloc(size + xr_reserved_tail);
}

void* xrMemory::mem_alloc(size_t size, const std::nothrow_t&) noexcept {
  return malloc(size + xr_reserved_tail);
}

void* xrMemory::mem_alloc(size_t size,
                          size_t alignment,
                          const std::nothrow_t&) noexcept {
  return malloc(size + xr_reserved_tail);
}

void* xrMemory::small_alloc(size_t size) noexcept {
  return malloc(size + xr_reserved_tail);
}

void xrMemory::small_free(void* ptr) noexcept {
  free(ptr);
}

void* xrMemory::mem_realloc(void* ptr, size_t size) {
  return realloc(ptr, size + xr_reserved_tail);
}

void* xrMemory::mem_realloc(void* ptr, size_t size, size_t alignment) {
  return realloc(ptr, size + xr_reserved_tail);
}

void xrMemory::mem_free(void* ptr) {
  free(ptr);
}

void xrMemory::mem_free(void* ptr, size_t alignment) {
  free(ptr);
}

pstr xr_strdup(pcstr string) {
  VERIFY(string);
  size_t len = strlen(string) + 1;
  auto memory = static_cast<char*>(xr_malloc(len));
  CopyMemory(memory, string, len);
  return memory;
}

[[nodiscard]] void* operator new(size_t size) {
  return Memory.mem_alloc(size);
}

[[nodiscard]] void* operator new[](size_t size) {
  return Memory.mem_alloc(size);
}

[[nodiscard]] void* operator new(size_t size, const std::nothrow_t&) noexcept {
  return Memory.mem_alloc(size);
}

[[nodiscard]] void* operator new[](size_t size,
                                   const std::nothrow_t&) noexcept {
  return Memory.mem_alloc(size);
}

[[nodiscard]] void* operator new(size_t size, std::align_val_t alignment) {
  return Memory.mem_alloc(size, static_cast<size_t>(alignment));
}

[[nodiscard]] void* operator new[](size_t size, std::align_val_t alignment) {
  return Memory.mem_alloc(size, static_cast<size_t>(alignment));
}

[[nodiscard]] void* operator new(size_t size,
                                 std::align_val_t alignment,
                                 const std::nothrow_t&) noexcept {
  return Memory.mem_alloc(size, static_cast<size_t>(alignment));
}

[[nodiscard]] void* operator new[](size_t size,
                                   std::align_val_t alignment,
                                   const std::nothrow_t&) noexcept {
  return Memory.mem_alloc(size, static_cast<size_t>(alignment));
}

void operator delete(void* ptr) noexcept {
  Memory.mem_free(ptr);
}

void operator delete[](void* ptr) noexcept {
  Memory.mem_free(ptr);
}

void operator delete(void* ptr, std::align_val_t alignment) noexcept {
  Memory.mem_free(ptr, static_cast<size_t>(alignment));
}

void operator delete[](void* ptr, std::align_val_t alignment) noexcept {
  Memory.mem_free(ptr, static_cast<size_t>(alignment));
}

void operator delete(void* ptr, size_t) noexcept {
  Memory.mem_free(ptr);
}

void operator delete[](void* ptr, size_t) noexcept {
  Memory.mem_free(ptr);
}

void operator delete(void* ptr, size_t, std::align_val_t alignment) noexcept {
  Memory.mem_free(ptr, static_cast<size_t>(alignment));
}

void operator delete[](void* ptr, size_t, std::align_val_t alignment) noexcept {
  Memory.mem_free(ptr, static_cast<size_t>(alignment));
}

void* xr_malloc(size_t size) {
  return Memory.mem_alloc(size);
}

void* xr_realloc(void* ptr, size_t size) {
  return Memory.mem_realloc(ptr, size);
}
