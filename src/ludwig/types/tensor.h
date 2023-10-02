#pragma once

#include <cstring>
#include "primitive.h"
#include "vector.h"

namespace ludwig
{
    template<typename T>
    struct Tensor
    {
        T*   data;
        u64  size;
        Vector<u32> dimensions;
        
        Tensor();
        Tensor(const Vector<u32>&);
        Tensor(const Vector<u32>&, const T&);
        Tensor(const u32&);
        Tensor(const u32&, const u32&);
        Tensor(const u32&, const u32&, const u32&);
        Tensor(const u32&, const u32&, const u32&, const u32&);
    

    };
    
    template<typename T>
    Tensor<T>::Tensor()
    {
        size = 1;
        dimensions = Vector<u32>(size, 1);
        data = new T[size];
        data[0] = 0.0;
    }
    

    template<typename T>
    Tensor<T>::Tensor(const Vector<u32>& dims) : dimensions(dims)
    {
        size = 1;
        for (u64 i = 0; i < dimensions.size; i++)
            size *= dimensions[i];

        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

            

}
