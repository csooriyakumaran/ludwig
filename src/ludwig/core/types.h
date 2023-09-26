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
    struct Mat1
    {
        T* data;
        u32 size;

        Mat1(u32 s) : size(s)
        {
            data = new T[size];
        }

        Mat1(u32 s, T init) : size(s)
        {
            data = new T[size];

            for (int i = 0; i < size; i++)
                data[i] = init;
        }
        ~Mat1()
        {
            delete[] data;
        }
        
        T& operator() (const u32 i)
        {
            return data[i];
        }
        const T& operator() (const u32 i) const
        {
            return data[i];
        }
    };

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
        const T& operator() (const u32 i, const u32 j) const
        {
            return data[i + j * rows];
        }
    };
}
