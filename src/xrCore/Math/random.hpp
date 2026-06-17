#pragma once

#include "Common/Platform.hpp"
#include "Common/types.hpp"
#include "xrCore/xrDebug_macros.h"

class CRandom {
  volatile s32 holdrand;

 public:
  CRandom() : holdrand(1) {};
  CRandom(s32 _seed) : holdrand(_seed) {};

  void seed(s32 val) { holdrand = val; }
  s32 maxI() { return 32767; }
  ICN s32 randI() noexcept {
    return (holdrand = holdrand * 214013L + 2531011L) >> 16 & 0x7fff;
  }
  s32 randI(s32 max) {
    VERIFY(max);
    return randI() % max;
  };
  s32 randI(s32 min, s32 max) { return min + randI(max - min); }
  s32 randIs(s32 range) { return randI(-range, range); }
  s32 randIs(s32 range, s32 offs) { return offs + randIs(range); }
  float maxF() { return 32767.f; }
  float randF() { return float(randI()) / maxF(); }
  float randF(float max) { return randF() * max; }
  float randF(float min, float max) { return min + randF(max - min); }
  float randFs(float range) { return randF(-range, range); }
  float randFs(float range, float offs) { return offs + randFs(range); }
};

extern CRandom Random;
