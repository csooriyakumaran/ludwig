#pragma once
#include <vector>
#include "vector.h"
#include "primitive.h"

namespace ludwig
{

    // since this will mostly be used for psuedo-2d analysis, and the third dimension is really only needed for cgns output, 
    // I don't want the k-wise data to be contiguous in memory. 

    // https://cgns.github.io/CGNS_docs_current/sids/gridflow.html
//looks like CGNS has 2D support, so maybe just drop the third dim .. 
    // since CNGS uses FORTRAN-like data layout, i will emulate that here. i.e., column-major 
    // question:: will it be better to have flat arrays for x,y,z etc. or better to have an array of pos vectors with x,y,z components? since at every position we're going to want to 
    template<typename T>
    struct Array3
    {
        T*  data;
        u32 ni;
        u32 nj;
        u32 nk;
        u64 size;

        Array3();
        Array3(const std::vector<u32>& shape);
        Array3(const u32 x, const u32 y, const u32 z);
        Array3(const u32 x, const u32 y, const u32 z, const T* init);
        Array3(const Array3<T>& rhs);
        Array3(Array3<T>&& rhs) noexcept;

        ~Array3();
        T& operator[] (const u64 i) noexcept;
        T& operator() (const u32 i, const u32 j, const u32 k) noexcept;

        const T& operator[] (const u64 i) const noexcept;
        const T& operator() (const u32 i, const u32 j, const u32 k) const noexcept;
        
        Array3<T> slice(const u32 i0, const u32 i1, const u32 j0, const u32 j1, const u32 k0, const u32 k1);
    };
    
    template<typename T>
    Array3<T>::Array3() : size(1), ni(1), nj(1), nk(1) 
    {
        data = new T[size];
        data[0] = static_cast<T>(0.0);
    }
    
    template<typename T>
    Array3<T>::Array3(const u32 x, const u32 y, const u32 z)
        : ni(x), nj(y), nk(z), size(x*y*z)
    {
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

    template<typename T>
    Array3<T>::Array3(const u32 x, const u32 y, const u32 z, const T* init)
        : ni(x), nj(y), nk(z), size(x*y*z)
    {
        data = new T[size];
        std::copy(init, init + size, data);
    }
    
    template<typename T>
    Array3<T>::~Array3()
    {
        if (data != nullptr)
            delete[] data;
    }

    template<typename T> 
    Array3<T> Array3<T>::slice(const u32 i0, const u32 leni, const u32 j0, const u32 lenj, const u32 k0, const u32 lenk)
    {
        T* tempdata = new T[leni * lenj * lenk];
        u64 index = 0;
        for (u32 i = i0; i < i0 + leni; i++)
            for (u32 j = j0; j < j0 + lenj; j++)
                for (u32 k = k0; k < k0+ lenk; k++)
                   tempdata[index++] = data[i + j*ni + k*ni*nj]; // since all k-data should be contiguous, maybe a std::copy is better here??
        Array3<T> res(leni, lenj, lenk, tempdata);
        delete[] tempdata;
        return res;
    }

}

