#pragma once

#include <stdint.h> 
#include <math.h>
#include <vector>
#include "../core/types.h"

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

    // NOTE(chris): this doesnt work yet
    static std::vector<f64> inflation_layer(f64 H, uint32_t N, f64 g)
    {
        
        std::vector<f64> y(N, 0);
        
        y[1] = H * (1 - g) / ( 1 - pow(g, N+1));

        for (int i=2; i < N; i++)
            y[i] = y[1] * pow(g, i-1);

        return y;
    }


    // TODO(chris): change indexing for maxtrix to use [i,j] instead of (i,j) to maintain consistency with std::vector
    template<typename T>
    void SolveTDMA(Mat2<T> A, std::vector<T> b, std::vector<T>& x)
    {
        uint32_t m = b.size();

        x.resize(m);

        // first row coefficients
        A(0,1) = A(0, 1) / A(0,0);
        b[0]   = b[0] / A(0,0);

        // forward elimination
        for ( int i = 1; i < m-1; i++)
        {
            T d = A(i,i) - A(i-1, i) * A(i, i-1);
            A(i, i+1) = A(i, i+1) / d;
            b[i]      = ( b[i]- A(i, i-1)*b[i-1] ) / d;
        }

        // last row
        x[m-1] = ( b[m-1] - A(m-1, m-2) * b[m-2] ) / ( A(m-1, m-1) - A(m-2,m-1)*A(m-1, m-2) );

        for (int i = m-2; i >= 0; i--)
            x[i] = -A(i, i+1)*x[i+1] + b[i];
    }
}

