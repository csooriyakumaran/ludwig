#pragma once

#include "vector.h"
#include "primitive.h"
#include "../core/assert.h"

namespace ludwig
{
    // ok what do i actually need: a 2D array for most CFD, maybe 3D, and at most 4D
    template<typename T>
    struct Array
    {
        T*          data;
        u64         size;
        Vec4<u32>   dims; // ni = Array.dims.x, nj = Array.dims.y, ..
        
        Array();
        Array(const u32);
        Array(const Vec2<u32>&);
        Array(const Vec3<u32>&);
        Array(const Vec4<u32>&);
        Array(const std::initializer_list<u32>&);
        Array(const u32 x = 1, const u32 y = 1, const u32 z = 1, const u32 t = 1);

        void initialize(const T&);
        void initialize(const Vector<T>&);

        T& operator[] (const u32);
        T& operator() (const u32 i = 0, const u32 j = 0, const u32 k = 0, const u32 t = 0) noexcept;
        const T& operator[] (const u32) const;
        const T& operator() (const u32 i = 0, const u32 j = 0, const u32 k = 0, const u32 t = 0) const noexcept;
    };
    template<typename T>
    Array<T>::Array() : dims({1,1,1,1}), size(1)
    {
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

    template<typename T>
    Array<T>::Array(const u32 s) : size(s)
    {
        dims.x = size; dims.y = 1; dims.z = 1;  dims.t = 1;
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

    template<typename T>
    Array<T>::Array(const Vec2<u32>& shape)
    {
        dims.x = shape.x; dims.y = shape.y; dims.z = 1;  dims.t = 1;
        size = dims.x * dims.y * dims.z * dims.t; 
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

    template<typename T>
    Array<T>::Array(const Vec3<u32>& shape)
    {
        dims.x = shape.x; dims.y = shape.y; dims.z = shape.z;  dims.t = 1;
        size = dims.x * dims.y * dims.z * dims.t; 
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

    template<typename T>
    Array<T>::Array(const Vec4<u32>& shape) : dims(shape), size(1)
    {
        size = dims.x * dims.y * dims.z * dims.t; 
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

    template<typename T>
    Array<T>::Array(const std::initializer_list<u32>& shape)
    {
        ASSERT(shape.size() < 5, "Arrays of Rank 5 and greater are not supported (yet?)!\n");
        dims = {1,1,1,1}; 
        if (shape.size() >= 1)
            dims.x = *shape.begin();
        if (shape.size() >= 2)
            dims.y = *(shape.begin()+1);
        if (shape.size() >= 3)
            dims.z = *(shape.begin()+2);
        if (shape.size() >= 4)
            dims.t = *(shape.begin()+3);

        size = dims.x * dims.y * dims.z * dims.t; 
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }
    template<typename T>
    Array<T>::Array(const u32 x, const u32 y, const u32 z, const u32 t)
    {
        dims = {x, y, z, t};
        size = dims.x * dims.y * dims.z * dims.t; 
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

    template<typename T>
    void Array<T>::initialize(const T& init)
    {
        for (u64 i = 0; i < size; i++)
            data[i] = init; 
    }

    template<typename T>
    void Array<T>::initialize(const Vector<T>& v)
    {
        ASSERT( (v.size == size), "Cannot initialize Array of length %d with a Vector of length %d\n", size, v.size);
        for (u64 i = 0; i < size; i++)
            data[i] = v[i]; 
    }

    template<typename T>
    T& Array<T>::operator[] (const u32 i)
    {
        ASSERT( (i < size), "Index %d is out of bounds for Array of size %d\n", i, size);
        return data[i];
    }

    template<typename T>
    const T& Array<T>::operator[] (const u32 i) const
    {
        ASSERT( (i < size), "Index %d is out of bounds for Array of size %d\n", i, size);
        return data[i];
    }

    template<typename T>
    T& Array<T>::operator() (const u32 i, const u32 j, const u32 k, const u32 t) noexcept
    {
        ASSERT( (i < dims.x), "Index i = %d in x-dim is out of bounds for Array of size %dx%dx%dx%d (i,j,k,t)\n", i, dims.x, dims.y, dims.z, dims.t);
        ASSERT( (j < dims.y), "Index j = %d in y-dim is out of bounds for Array of size %dx%dx%dx%d (i,j,k,t)\n", j, dims.x, dims.y, dims.z, dims.t);
        ASSERT( (k < dims.z), "Index k = %d in z-dim is out of bounds for Array of size %dx%dx%dx%d (i,j,k,t)\n", k, dims.x, dims.y, dims.z, dims.t);
        ASSERT( (t < dims.t), "Index t = %d in t-dim is out of bounds for Array of size %dx%dx%dx%d (i,j,k,t)\n", t, dims.x, dims.y, dims.z, dims.t);
        return data[i + j * dims.x + k * dims.x * dims.y + t * dims.x*dims.y*dims.z];
    }

    template<typename T>
    const T& Array<T>::operator() (const u32 i, const u32 j, const u32 k, const u32 t) const noexcept
    {
        ASSERT( (i < dims.x), "Index i = %d in x-dim is out of bounds for Array of size %dx%dx%dx%d (i,j,k,t)\n", i, dims.x, dims.y, dims.z, dims.t);
        ASSERT( (j < dims.y), "Index j = %d in y-dim is out of bounds for Array of size %dx%dx%dx%d (i,j,k,t)\n", j, dims.x, dims.y, dims.z, dims.t);
        ASSERT( (k < dims.z), "Index k = %d in z-dim is out of bounds for Array of size %dx%dx%dx%d (i,j,k,t)\n", k, dims.x, dims.y, dims.z, dims.t);
        ASSERT( (t < dims.t), "Index t = %d in t-dim is out of bounds for Array of size %dx%dx%dx%d (i,j,k,t)\n", t, dims.x, dims.y, dims.z, dims.t);
        return data[i + j * dims.x + k * dims.x * dims.y + t * dims.x*dims.y*dims.z];
    }








    // TODO(chris):
    //  [ ] Add element-by-element arithmatic. 
    //  [ ] Add reduce methode to drop one (specified) dimension
    //  [ ] Add ability to set a full dimension from a Vector

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
        Array3(const u32, const u32, const u32);
        Array3(const u32, const u32, const u32, const T*);
        Array3(const Vec3<u32>&);
        Array3(const Array3<T>&);
        Array3(Array3<T>&&) noexcept;

        ~Array3();

        T& operator[] (const u64) noexcept;
        T& operator() (const u32, const u32, const u32) noexcept;

        const T& operator[] (const u64) const noexcept;
        const T& operator() (const u32, const u32, const u32) const noexcept;
       
        Array3<T>& operator= (const Array3<T>&);
        Array3<T>& operator= (Array3<T>&&) noexcept;

        Array3<T> slice(const u32 i0, const u32 i1, const u32 j0, const u32 j1, const u32 k0, const u32 k1);
        void emplace_x(const Vector<T>&, const u32, const u32);
        void emplace_y(const Vector<T>&, const u32, const u32);
        void emplace_z(const Vector<T>&, const u32, const u32);
    };
    
    template<typename T>
    Array3<T>::Array3()
        : size(1), ni(1), nj(1), nk(1)
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
    Array3<T>::Array3(const Vec3<u32>& d) : ni(d.x), nj(d.y), nk(d.z), size(d.x * d.y * d.z)
    {
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

    template<typename T>
    Array3<T>::Array3(const Array3<T>& rhs) : ni(rhs.ni), nj(rhs.nj), nk(rhs.nk), size(rhs.size)
    {
        data = new T[size];
        std::copy(rhs.data, rhs.data + size, data);
    }

    template<typename T>
    Array3<T>::Array3(Array3<T>&& rhs) noexcept : ni(0), nj(0), nk(0), size(0), data(nullptr)
    {
        *this = std::move(rhs);
    }

    template<typename T>
    Array3<T>::~Array3()
    {
        if (data != nullptr)
            delete[] data;
    }

    template<typename T>
    T& Array3<T>::operator[] (const u64 i) noexcept
    {
        ASSERT( (i < size), "Index out of bounds at i = %d\n", i);
        return data[i];
    }

    template<typename T>
    T& Array3<T>::operator() (const u32 i, const u32 j, const u32 k) noexcept
    {
        ASSERT( (i < ni), "Index out of bounds at i = %d\n", i);
        ASSERT( (j < nj), "Index out of bounds at j = %d\n", j);
        ASSERT( (k < nk), "Index out of bounds at k = %d\n", k);
        return data[i + j*ni + k*ni*nj];
    }

    template<typename T>
    const T& Array3<T>::operator[] (const u64 i) const noexcept
    {
        ASSERT( (i < size), "Index out of bounds at i = %d\n", i);
        return data[i];
    }

    template<typename T>
    const T& Array3<T>::operator() (const u32 i, const u32 j, const u32 k) const noexcept
    {
        ASSERT( (i < ni), "Index out of bounds at i = %d\n", i);
        ASSERT( (j < nj), "Index out of bounds at j = %d\n", j);
        ASSERT( (k < nk), "Index out of bounds at k = %d\n", k);
        return data[i + j*ni + k*ni*nj];
    }

    template<typename T>
    Array3<T>& Array3<T>::operator= (const Array3<T>& rhs)
    {
        if ( this != &rhs )
        {
            if ( data != nullptr )
                delete[] data;
            
            ni = rhs.ni;
            nj = rhs.nj;
            nk = rhs.nk;
            size = rhs.size;
            data = new T[size];
            std::copy(rhs.data, rhs.data + size, data);
        }
        return *this;
    }

    template<typename T>
    Array3<T>& Array3<T>::operator= (Array3<T>&& rhs) noexcept
    {
        if ( this != &rhs )
        {
            if ( data != nullptr )
                delete[] data;
            
            ni = rhs.ni;
            nj = rhs.nj;
            nk = rhs.nk;
            size = rhs.size;
            data = rhs.data; 
            
            rhs.ni = 0;
            rhs.nj = 0;
            rhs.nk = 0;
            rhs.size = 0;
            rhs.data = nullptr;
        }
        return *this;
    }
    
    template<typename T> 
    Array3<T> Array3<T>::slice(const u32 i0, const u32 leni, const u32 j0, const u32 lenj, const u32 k0, const u32 lenk)
    {
        ASSERT( (i0 + leni <= ni), "Cannot slice array: too many i-elements requested\n");
        ASSERT( (j0 + lenj <= nj), "Cannot slice array: too many j-elements requested\n");
        ASSERT( (k0 + lenk <= nk), "Cannot slice array: too many k-elements requested\n");
        T* tempdata = new T[leni * lenj * lenk];
        u64 index = 0;
        for (u32 k = k0; k < k0+ lenk; k++)
            for (u32 j = j0; j < j0 + lenj; j++)
                for (u32 i = i0; i < i0 + leni; i++)
                   tempdata[index++] = data[i + j*ni + k*ni*nj]; 
        Array3<T> res(leni, lenj, lenk, tempdata);
        delete[] tempdata;
        return res;
    }

    template<typename T>
    void Array3<T>::emplace_x(const Vector<T>& v, const u32 j, const u32 k)
    {
        ASSERT( (v.size == ni), "Dimensions do not matach, cannot emplace data in x-direction\n");
        u32 stride = 1;
        u32 offset = j*ni + k*ni*nj;

        for (u32 i = 0; i < v.size; i++)
            data[i*stride + offset] = v[i];
    }

    template<typename T>
    void Array3<T>::emplace_y(const Vector<T>& v, const u32 i, const u32 k)
    {
        ASSERT( (v.size == nj), "Dimensions do not matach, cannot emplace data in y-direction\n");
        u32 stride = ni;
        u32 offset = i + k*ni*nj;

        for (u32 j = 0; j < v.size; j++)
            data[j*stride + offset] = v[j];
    }

    template<typename T>
    void Array3<T>::emplace_z(const Vector<T>& v, const u32 i, const u32 j)
    {
        ASSERT( (v.size == nk), "Dimensions do not matach, cannot emplace data in z-direction\n");
        u32 stride = ni*nj;
        u32 offset = i + j*ni;

        for (u32 k = 0; k < v.size; k++)
            data[k*stride + offset] = v[k];
    }

}
