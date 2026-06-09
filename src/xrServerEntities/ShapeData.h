#pragma once

#include "Common/types.hpp"
#include "xrCore/Math/sphere.hpp"
#include "xrCore/Math/matrix.hpp"
#include "xrCommon/xr_vector.h"

struct CShapeData
{
    enum
    {
        cfSphere = 0,
        cfBox
    };

    union shape_data
    {
        Fsphere sphere;
        Fmatrix box;
    };

    struct shape_def
    {
        u8 type;
        shape_data data;
    };
    using ShapeVec = xr_vector<shape_def>;
    ShapeVec shapes;
};
