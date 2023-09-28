#pragma once

#include <stdint.h> 
#include <math.h>
#include <vector>
#include "../types/types.h"

namespace ludwig
{
    struct Vertex
    {
        f64 x;
        f64 y;
    };

    struct FlowField
    {
        std::vector<Vertex> vertices;
        std::vector<f64>    u;
        std::vector<f64>    v;
        std::vector<f64>    p;
        std::vector<f64>    rho; // density
        std::vector<f64>    mu;
    };

    // this doesnt work yet
    static std::vector<f64> inflation_layer(f64 H, uint32_t N, f64 g)
    {
        
        std::vector<f64> y(N, 0);
        
        y[1] = H * (1 - g) / ( 1 - pow(g, N+1));

        for (int i=2; i < N; i++)
            y[i] = y[1] * pow(g, i-1);

        return y;
    }
}

