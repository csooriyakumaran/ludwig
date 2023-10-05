#pragma once

#include "../types/types.h"

namespace ludwig 
{
    typedef Array<f64>       ScalarField;
    typedef Array<Vec2<f64>> VectorField;
    
    struct FlowField
    {
        VectorField position; // position(i,j).x
        VectorField velocity; // u = velocity(i,j).x, v = velocity(i,j).y
        ScalarField pressure; // pressure(i,j)
        ScalarField density;
        ScalarField viscosity;
    };

   // FlowField make_flow_field(Mesh& mesh, 
}
