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



 // void MOC2::optimize::gradient_descent(std::vector<f64> inputs, NozzleGeometry& geom, std::function<f64(std::vector<f64>) cost_func)
// {
//      f64 cost = 0.0;
//      for (u32 i = 0; i < MAX_IT; i++)
//          
