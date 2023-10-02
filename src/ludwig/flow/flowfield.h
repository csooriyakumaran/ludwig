#pragma once

#include "../types/types.h"

namespace ludwig
{
    struct FlowField
    {
        Array3<Vec3<f64>> position;
        Array3<Vec3<f64>> velocity;
        Array3<Vec3<f64>> stress_x;
        Array3<Vec3<f64>> stress_y;
        Array3<Vec3<f64>> stress_z;
        Array3<f64>       pressure;
        Array3<f64>       density;
        Array3<f64>       viscosity;
    };
}
