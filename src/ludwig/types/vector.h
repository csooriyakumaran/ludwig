#pragma once

#include "primitive.h"

namespace ludwig
{
    // =========================== VECTORS =================================
    // - these are mathematical vectros with n singl-element components
    template<typename T>
    struct Vec2
    {
        T x;
        T y;
    };

    template<typename T>
    struct Vec3
    {
        T x;
        T y;
        T z;
    };

    template<typename T>
    struct Vec4
    {
        T x;
        T y;
        T z;
        T t;
    };

    template<typename T>
    Vec2<T> operator+ (const Vec2<T>& lhs, const Vec2<T>& rhs)
    {
        Vec2<T> res = {lhs.x + rhs.x, lhs.y + rhs.y};
        return res;
    }

    // forward declaration
    template<typename T> 
    struct Matrix;

    template<typename T>
    struct Vector
    {
        T* data;
        u64 size;
    
        Vector();
        Vector(u64 s);
        Vector(u64 s, const T init);
        Vector(u64 s, const T* init);
        Vector(std::initializer_list<T> init);
        Vector(const Vector<T>& rhs);
        Vector(Vector<T>&& rhs) noexcept;
        
        ~Vector();
        
        T& operator[] (const u64 i) noexcept;
        T& operator() (const u64 i) noexcept;
        
        const T& operator[] (const u64 i) const noexcept;
        const T& operator() (const u64 i) const noexcept;

        Vector<T>& operator= (const Vector<T>& rhs) noexcept;
        Vector<T>& operator= (Vector<T>&& rhs) noexcept;

        bool operator== (const Vector<T>& rhs) const;
        bool operator== (const Matrix<T>& rhs) const;
        
        Vector<T>& operator+= (const T& rhs);
        Vector<T>& operator-= (const T& rhs);
        Vector<T>& operator*= (const T& rhs);

        Vector<T>& operator+= (const Vector<T>& rhs);
        Vector<T>& operator-= (const Vector<T>& rhs);
    
        template<typename U> friend Vector<U> operator+ (const U& lhs, const Vector<U>& rhs);
        template<typename U> friend Vector<U> operator- (const U& lhs, const Vector<U>& rhs);
        template<typename U> friend Vector<U> operator* (const U& lhs, const Vector<U>& rhs);

        static T& dot(const Vector<T>& lhs, const Vector<T>& rhs);
        static Vector<T>& cross(const Vector<T>& lhs, const Vector<T>& rhs); // only if n = 3;
        
        const T& magnitude();
        
    };

    // ====================================================================== //
    // constructors 
    // ====================================================================== //
    template<typename T>
    Vector<T>::Vector() : size(1)
    {
        data = new T[size];
        data[0] = static_cast<T>(0.0);
    }

    template<typename T>
    Vector<T>::Vector(u64 s) : size(s)
    {
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

    template<typename T>
    Vector<T>::Vector(u64 s, const T init) : size(s)
    {
        data = new T[size];
        for (u64 i = 0; i < size; i++)
            data[i] = init;
    }

    template<typename T>
    Vector<T>::Vector(u64 s, const T* init) : size(s)
    {
        data = new T[size];
        std::copy(init, init + size, data);
    }

    template<typename T>
    Vector<T>::Vector(std::initializer_list<T> init)
    {
        size = init.size();
        data = new T[size];
        std::copy(init.begin(), init.end(), data);
    }

    template<typename T>
    Vector<T>::Vector(const Vector<T>& rhs) : size(rhs.size)
    {
        data = new T[size];
        std::copy(rhs.data, rhs.data + size, data);
    }

    template<typename T>
    Vector<T>::Vector(Vector<T>&& rhs) noexcept : data(nullptr),  size(0)
    {
        *this = std::move(rhs);
    }

    template<typename T>
    Vector<T>::~Vector()
    {
        if (data != nullptr)
            delete[] data;
    }
    // ====================================================================== //
    // member operator overloads 
    // ====================================================================== //
    template<typename T>
    T& Vector<T>::operator[] (const u64 i) noexcept
    {
        ASSERT( (i < size), "Array out of bounds: i = %d > size = %d\n", i, size);
        return data[i];
    }

    template<typename T>
    T& Vector<T>::operator() (const u64 i) noexcept
    {
        ASSERT( (i < size), "Array out of bounds: i = %d > size = %d\n", i, size);
        return data[i];
    }

    template<typename T>
    const T& Vector<T>::operator[] (const u64 i) const noexcept
    {
        ASSERT( (i < size), "Array out of bounds: i = %d > size = %d\n", i, size);
        return data[i];
    }

    template<typename T>
    const T& Vector<T>::operator() (const u64 i) const noexcept
    {
        ASSERT( (i < size), "Array out of bounds: i = %d > size = %d\n", i, size);
        return data[i];
    }
    
    template<typename T>
    Vector<T>& Vector<T>::operator= (const Vector<T>& rhs) noexcept
    {
        if ( this != &rhs )
        {
            if ( data != nullptr )
                delete[] data;

            size = rhs.size;
            data = new T[size];
            std::copy(rhs.data, rhs.data + size, data);
        }
        return *this;
    }

    template<typename T>
    Vector<T>& Vector<T>::operator= (Vector<T>&& rhs) noexcept
    {
        if ( this != &rhs )
        {
            if ( data != nullptr )
                delete[] data;

            data = rhs.data;
            size = rhs.size;
            rhs.data = nullptr;
            rhs.size = 0;
        }
        return *this;
    }
}
