#pragma once

#include <stdint.h> 

namespace ludwig
{
    typedef uint32_t u32;
    typedef int32_t  i32;

    typedef uint64_t u64;
    typedef int64_t  i64;

    typedef double   f64;
    typedef float    f32;

    template<typename T>
    struct Mat2
    {
        T*  data;
        u32 rows;
        u32 cols;
        u64 size;

        Mat2(u32 r, u32 c) : rows(r), cols(c)
        {
            size = r*c;
            data = new T[size];
        }
        
        Mat2(u32 r, u32 c, T init) : rows(r), cols(c)
        {
            size = r*c;
            data = new T[size];
            
            for (int i = 0; i < size; i++)
                data[i] = init;
        }

        ~Mat2()
        {
            delete[] data;
        }

        T& operator() (const u32 i, const u32 j)
        {
            return data[i + j * rows];
        }
    };
}
