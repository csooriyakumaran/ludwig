#pragma once

#include "../core/types.h"

namespace ludwig
{
    struct Geometry 
    {
        Mat2<f64> x;
        Mat2<f64> y;

        Geometry(u32 X, u32 Y);
    };
}
