#pragma once
#include "xrCore/xrMemory.h"

template <class T>
class destructor {
  T* ptr;

 public:
  destructor(T* p) { ptr = p; }
  ~destructor() { xr_delete(ptr); }
  T& operator()() { return *ptr; }
};
