#pragma once

#include "primitive.h"

namespace ludwig
{

    // =========================== ARRAYS =================================
    // - these are n-dimensional arrays that store data to be operated on 
    //   in an element-by-element fashion
    template<typename T, size_t nDims> 
    struct Array
    {
        T*   data;
        u32* dims;
        u32  size;
        
        Array(u32* shape) : dims(shape)
        {
            size = 0;
            for (int i = 0; i < nDims; i++)
                size *= shape[i];

            data = new T[size];
            memset(data, 0, size*sizeof(*data));
        }

        ~Array()
        {
            if (data != nullptr)
                delete[] data;
        }
    };

}
