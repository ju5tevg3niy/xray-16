#include "xrCore/LocatorAPI.h"
#pragma once

#include "Common/types.hpp"
#include "xrCore/Math/flags.hpp"

#ifdef DEBUG
extern bool bDebug;
#else
#define bDebug 0
#endif

extern bool CallOfPripyatMode;
extern bool ClearSkyMode;
extern bool ShadowOfChernobylMode;

// textures
extern int psTextureLOD;

// psDeviceFlags
enum
{
    rsAlwaysActive          = (1ul << 0ul),
    rsClearBB               = (1ul << 1ul),
    rsVSync                 = (1ul << 2ul),
    rsWireframe             = (1ul << 3ul),

    rsConstantFPS           = (1ul << 4ul),
    rsDisableObjectsAsCrows = (1ul << 5ul),

    rsStatistic             = (1ul << 6ul),
    rsCameraPos             = (1ul << 7ul),
    rsShowFPS               = (1ul << 8ul),
    rsShowFPSGraph          = (1ul << 9ul),
    rsOcclusionDraw         = (1ul << 10ul),

    rsDrawStatic            = (1ul << 11ul),
    rsDrawDynamic           = (1ul << 12ul),
    rsDrawDetails           = (1ul << 13ul),
    rsDrawParticles         = (1ul << 14ul),

    mtSound                 = (1ul << 15ul),
    mtPhysics               = (1ul << 16ul),
    mtNetwork               = (1ul << 17ul),
    mtParticles             = (1ul << 18ul),

    // 20-32 bit - reserved to Editor
};

enum
{
    rsWindowed,
    rsWindowedBorderless,
    rsFullscreenBorderless, // windowed + topmost + window is scaled to desktop resolution + without borders = looks like fullscreen
    rsFullscreen,           // true, exclusive fullscreen
};

struct DeviceMode
{
    u32 Monitor;
    u32 WindowStyle;
    u32 Width;
    u32 Height;
    u32 RefreshRate;
    u32 BitsPerPixel;
};

extern DeviceMode psDeviceMode;
extern Flags32 psDeviceFlags;

#include "Common/FSMacros.hpp"
