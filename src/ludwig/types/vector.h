#pragma once

#include <cmath>
#include "primitive.h"

namespace ludwig
{
    // =========================== VECTORS ====================================
    // - these are mathematical vectors with n singl-element components

    // ===========================   Vec2   ===================================
    template<typename T> struct Vec2 { T x; T y; };

    template<typename T> Vec2<T> operator+ (const Vec2<T>& lhs, const Vec2<T>& rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; }

    template<typename T> Vec2<T> operator- (const Vec2<T>& lhs, const Vec2<T>& rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y}; }

    template<typename T> Vec2<T> operator* (const Vec2<T>& lhs, const T& rhs) { return {lhs.x * rhs, lhs.y * rhs}; }

    template<typename T> Vec2<T> operator* (const T& lhs, const Vec2<T>& rhs) { return {lhs * rhs.x, lhs * rhs.y}; }

    template<typename T> T magnitude(const Vec2<T>& v) { return std::sqrt(v.x * v.x + v.y * v.y); }

    template<typename T> T dot(const Vec2<T>& lhs, const Vec2<T>& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

    // ===========================   Vec3   ===================================
    template<typename T> struct Vec3 { T x; T y; T z; };

    template<typename T> Vec3<T> operator+ (const Vec3<T>& lhs, const Vec3<T>& rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}; }

    template<typename T> Vec3<T> operator- (const Vec3<T>& lhs, const Vec3<T>& rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z}; }

    template<typename T> Vec3<T> operator* (const Vec3<T>& lhs, const T& rhs) { return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs}; }

    template<typename T> Vec3<T> operator* (const T& lhs, const Vec3<T>& rhs) { return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z}; }

    template<typename T> T magnitude(const Vec3<T>& v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

    template<typename T> T dot(const Vec3<T>& lhs, const Vec3<T>& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }

    template<typename T> Vec3<T> cross(const Vec3<T>& lhs, const Vec3<T>& rhs) { return  {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x}; }

    // ===========================   Vec4   ===================================
    template<typename T> struct Vec4 { T x; T y; T z; T t; };

    template<typename T> Vec4<T> operator+ (const Vec4<T>& lhs, const Vec4<T>& rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.t + rhs.t}; }

    template<typename T> Vec4<T> operator- (const Vec4<T>& lhs, const Vec3<T>& rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.t - rhs.t}; }

    template<typename T> Vec4<T> operator* (const Vec4<T>& lhs, const T& rhs) { return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.t * rhs}; }

    template<typename T> Vec4<T> operator* (const T& lhs, const Vec4<T>& rhs) { return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.t}; }

    template<typename T> T magnitude(const Vec4<T>& v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.t * v.t); }

    template<typename T> T dot(const Vec4<T>& lhs, const Vec3<T>& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.t * rhs.t; }
    // ========================================================================

    // ========================= N-DIMENSIONAL VECTORS ======================== 
    // forward declaration 
    template<typename T> struct Matrix;

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
