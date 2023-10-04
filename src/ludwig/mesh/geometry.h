#pragma once

#include "../types/types.h"
#include "uniform-grid.h"

namespace ludwig
{

    struct Vertex : public Vec2<f64> // x, y, id
    {
        u64 id;
    };

    struct Edge
    {
        Vector<Vertex> vertices;
        Vector<Vec2<f64>> norms;

        Edge(Vector<Vertex>& v) : vertices(v)
        {
            for (u64 i = 0; i < v.size - 1; i++)
                norms[i] = normalizeVector(Vec2<f64>( (v[i+1].y - v[i].y), -(v[i+1].x - v[i].x) ));
        }
        
        f64 len()
        {
            f64 length = 0.0;
            for (u64 i = 0; i <vertices.size; i++)
                length += std::sqrt( vertices[i].x * vertices[i].x + vertices[i].y * vertices[i].y );
            return length;
        }
        
        
    };

    
         
    enum class BoundaryType : u8
    {
        Wall = 0,
        Inlet, 
        Outlet, 
        Symmetry,
    };
    struct Boundary
    {
        Vector<Vec3<f64>> vertexes;
        
    };
    struct Geometry 
    {
        Vector<Vertex> vertices;
        Vector<Edge>   edges;
        

        Geometry(u32 X, u32 Y);
    };
}
