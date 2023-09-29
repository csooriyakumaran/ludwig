#pragma once

#include "primitive.h"
#include <vector>

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
        T w;

    };
    
    template<typename T>
    struct Vector
    {
        T* data;
        u64 size;
    
        Vector() : size(1)
        {
            data = new T[size];
            data[0] = 0.0;
        }

        Vector(u64 s) : size(s)
        {
            data = new T[size];
            memset(data, 0, size*sizeof(*data));
        }

        Vector(u64 s, const T init) : size(s)
        {
            data = new T[size];
            for (u64 i = 0; i < size; i++)
                data[i] = init;
        }
        
        Vector(u64 s, const T* init) : size(s)
        {
            data = new T[size];
            memcpy(data, init, size*sizeof(*data));
        }
        
        ~Vector()
        {
            if (data != nullptr)
                delete[] data;
        }
        
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
        void normalize(); // 1/mag * Vector
        Vector<T>& normalize();
        
    };


}
