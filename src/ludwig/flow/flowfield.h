#pragma once

#include "../types/types.h"

namespace ludwig
{
    struct FlowField2D
    {
        Array2<Vec2<f64>> position;
        Array2<Vec2<f64>> velocity;
        Array2<Vec2<f64>> stress_x;
        Array2<Vec2<f64>> stress_y;
        Array2<Vec2<f64>> stress_z;
        Array2<f64>       pressure;
        Array2<f64>       density;
        Array2<f64>       viscosity;
    };
}
