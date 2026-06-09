// XXX tamlin: This header is a HOG! It includes tons of headers, while it's the ONLY
// place defining f.ex. fsimilar, deg2rad, clampr. Split it up!
#pragma once

#include "xrCore/Math/constants.hpp"
// Define types and namespaces (CPU & FPU)
#include "Common/types.hpp"
#include "xrCore/cpu.hpp"
#include "xrCore/Math/bitwise.hpp"
#include "_std_extensions.h"
#include "xrCore/Math/math_funcs_inline.hpp"

struct Fquaternion;

#pragma pack(push)
#pragma pack(1)

#include "xrCore/Math/color.hpp"
#include "xrCore/Math/vector3.hpp"
#include "xrCore/Math/vector2.hpp"
#include "xrCore/Math/vector4.hpp"
#include "xrCore/Math/matrix.hpp"
#include "xrCore/Math/matrix33.hpp"
#include "xrCore/Math/quaternion.hpp"
#include "xrCore/Math/rect.hpp"
#include "xrCore/Math/fbox.hpp"
#include "xrCore/Math/fbox2.hpp"
#include "xrCore/Math/obb.hpp"
#include "xrCore/Math/sphere.hpp"
#include "xrCore/Math/cylinder.hpp"
#include "xrCore/Math/random.hpp"
#include "xrCore/Math/compressed_normal.hpp"
#include "xrCore/Math/plane.hpp"
#include "xrCore/Math/plane2.hpp"
#include "xrCore/Math/flags.hpp"
#include "xrCore/Math/math_funcs.hpp"
#ifdef DEBUG
#include "dump_string.h"
#endif
#pragma pack(pop)
