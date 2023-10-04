#pragma once

#include "../types/types.h"

namespace ludwig
{
    typedef Array<f64>       ScalarField;
    typedef Array<Vec3<f64>> VectorField;
    
    struct FlowField2D
    {
        VectorField position; // position[i].x
        VectorField velocity;
        VectorField stress_x;
        VectorField stress_y;
        VectorField stress_z;
        ScalarField pressure; // pressure[i]
        ScalarField density;
        ScalarField viscosity;
    };
}
