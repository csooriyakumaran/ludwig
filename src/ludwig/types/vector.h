#pragma once

#include <iostream>
#include <cmath>

#include "primitive.h"

namespace ludwig
{
// =========================== VECTORS ========================================
    // - these are mathematical vectors with n singl-element components

// ===========================  Vec2   ========================================
    template<typename T> struct Vec2 { T x; T y; };

    template<typename T> Vec2<T> operator+ (const Vec2<T>& lhs, const Vec2<T>& rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; }

    template<typename T> Vec2<T> operator- (const Vec2<T>& lhs, const Vec2<T>& rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y}; }

    template<typename T> Vec2<T> operator* (const Vec2<T>& lhs, const T& rhs) { return {lhs.x * rhs, lhs.y * rhs}; }

    template<typename T> Vec2<T> operator* (const T& lhs, const Vec2<T>& rhs) { return {lhs * rhs.x, lhs * rhs.y}; }

    template<typename T> bool operator== (const Vec2<T>& lhs, const Vec2<T>& rhs) { return (lhs.x == rhs.x) && (lhs.y == rhs.y); }

    template<typename T> T vectorMagnitude(const Vec2<T>& v) { return std::sqrt(v.x * v.x + v.y * v.y); }

    template<typename T> T vectorDotProduct(const Vec2<T>& lhs, const Vec2<T>& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

    template<typename T> T vectorAngle(const Vec2<T>& lhs, const Vec2<T>& rhs) { return (vectorMagnitude(lhs) == 0 || vectorMagnitude(rhs) == 0) ? static_cast<T>(0.0) : std::acos(vectorDotProduct(lhs, rhs) / (vectorMagnitude(lhs) *  vectorMagnitude(rhs)) ); }

    template<typename T> Vec2<T> normalizeVector(const Vec2<T>& lhs) { T mag = vectorMagnitude(lhs); return ( mag == 0) ? Vec2<T>( static_cast<T>(0.0), static_cast<T>(0.0) ) : Vec2<T>( lhs.x / mag, lhs.y / mag ); } 

    template<typename T> std::ostream& operator<< (std::ostream& os, const Vec2<T>& v) { return os << "(" << v.x << ", " << v.y <<")"; }

// ===========================  Vec3   ========================================
    template<typename T> struct Vec3 { T x; T y; T z; };

    template<typename T> Vec3<T> operator+ (const Vec3<T>& lhs, const Vec3<T>& rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}; }

    template<typename T> Vec3<T> operator- (const Vec3<T>& lhs, const Vec3<T>& rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z}; }

    template<typename T> Vec3<T> operator* (const Vec3<T>& lhs, const T& rhs) { return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs}; }

    template<typename T> Vec3<T> operator* (const T& lhs, const Vec3<T>& rhs) { return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z}; }

    template<typename T> bool operator== (const Vec3<T>& lhs, const Vec3<T>& rhs) { return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z); }

    template<typename T> T vectorMagnitude(const Vec3<T>& v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

    template<typename T> T vectorDotProduct(const Vec3<T>& lhs, const Vec3<T>& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }

    template<typename T> Vec3<T> vectorCrossProduct(const Vec3<T>& lhs, const Vec3<T>& rhs) { return  {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x}; }

    template<typename T> T vectorAngle(const Vec3<T>& lhs, const Vec3<T>& rhs) { return (vectorMagnitude(lhs) == 0 || vectorMagnitude(rhs) == 0) ? static_cast<T>(0.0) : std::acos(vectorDotProduct(lhs, rhs) / (vectorMagnitude(lhs) *  vectorMagnitude(rhs)) ); }

    template<typename T> Vec3<T> normalizeVector(const Vec3<T>& lhs) { T mag = vectorMagnitude(lhs); return ( mag == 0) ? Vec3<T>( static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0) ) : Vec3<T>( lhs.x / mag, lhs.y / mag, lhs.z / mag ); } 

    template<typename T> std::ostream& operator<< (std::ostream& os, const Vec3<T>& v) { return os << "(" << v.x << ", " << v.y << ", " << v.z << ")"; }

// ===========================  Vec4   ========================================
    template<typename T> struct Vec4 { T x; T y; T z; T t; };

    template<typename T> Vec4<T> operator+ (const Vec4<T>& lhs, const Vec4<T>& rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.t + rhs.t}; }

    template<typename T> Vec4<T> operator- (const Vec4<T>& lhs, const Vec4<T>& rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.t - rhs.t}; }

    template<typename T> Vec4<T> operator* (const Vec4<T>& lhs, const T& rhs) { return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.t * rhs}; }

    template<typename T> Vec4<T> operator* (const T& lhs, const Vec4<T>& rhs) { return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.t}; }

    template<typename T> bool operator== (const Vec4<T>& lhs, const Vec4<T>& rhs) { return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) && (lhs.t == rhs.t); }

    template<typename T> T vectorMagnitude(const Vec4<T>& v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.t * v.t); }

    template<typename T> T vectorDotProduct(const Vec4<T>& lhs, const Vec4<T>& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.t * rhs.t; }

    template<typename T> T vectorAngle(const Vec4<T>& lhs, const Vec4<T>& rhs) { return (vectorMagnitude(lhs) == 0 || vectorMagnitude(rhs) == 0) ? static_cast<T>(0.0) : std::acos(vectorDotProduct(lhs, rhs) / (vectorMagnitude(lhs) *  vectorMagnitude(rhs)) ); }

    template<typename T> Vec4<T> normalizeVector(const Vec4<T>& lhs) { T mag = vectorMagnitude(lhs); return ( mag == 0) ? Vec4<T>( static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0) ) : Vec4<T>( lhs.x / mag, lhs.y / mag, lhs.z / mag, lhs.t / mag ); } 

    template<typename T> std::ostream& operator<< (std::ostream& os, const Vec4<T>& v) { return os << "(" << v.x << ", " << v.y << ", " << v.z <<  ", " << v.t << ")"; }

// ============================================================================


// ========================= N-DIMENSIONAL VECTORS ============================
    // forward declaration 
    template<typename T> struct Matrix;

    template<typename T>
    struct Vector
    {
        T* data;
        u64 size;
    
        Vector();
        explicit Vector(u64 s);
        explicit Vector(u64 s, const T init);
        explicit Vector(u64 s, const T* init);
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

        const T& vectorMagnitude();
        static T vectorDotProduct(const Vector<T>& lhs, const Vector<T>& rhs);
        static Vector<T>& vectorCrossProduct(const Vector<T>& lhs, const Vector<T>& rhs); // only if n = 3;
        
    };

    // ====================================================================== //
    // constructors 
    // ====================================================================== //
    template<typename T> Vector<T>::Vector() : size(1), data(new T[1]) { data[0] = static_cast<T>(0.0); }

    template<typename T> Vector<T>::Vector(u64 s) : size(s), data(new T[s]) { memset(data, 0, size*sizeof(*data)); }

    template<typename T> Vector<T>::Vector(u64 s, const T init) : size(s), data(new T[s]) { for (u64 i = 0; i < size; i++) data[i] = init; }

    template<typename T> Vector<T>::Vector(u64 s, const T* init) : size(s), data(new T[s]) { std::copy(init, init + size, data); }

    template<typename T> Vector<T>::Vector(std::initializer_list<T> init) : size(init.size()), data(new T[init.size()]) { std::copy(init.begin(), init.end(), data); }

    template<typename T> Vector<T>::Vector(const Vector<T>& rhs) : size(rhs.size), data(new T[rhs.size]) { std::copy(rhs.data, rhs.data + size, data); }

    template<typename T> Vector<T>::Vector(Vector<T>&& rhs) noexcept : data(nullptr),  size(0) { *this = std::move(rhs); }

    template<typename T> Vector<T>::~Vector() { if (data != nullptr) delete[] data; }

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
    // ====================================================================== //
    // static member functions
    // ====================================================================== //

    template<typename T>
    T Vector<T>::vectorDotProduct(const Vector<T>& lhs, const Vector<T>& rhs) 
    {
        ASSERT(lhs.size == rhs.size, "Cannot compute the dot product of vectors of different length\n");
        T res = 0;
        for (u64 i = 0; i < lhs.size; i++)
           res += lhs[i] * rhs[i];  

        return res;
    }
}
