#pragma once
#include <stdexcept>
#include "primitive.h"

#include <cstring>

// =========================== MATRICES =======================================
// - these are algebreaic matrices which follow typical matrix arithematic 
//   rules. The memory is layed out in row-major format so looping over dim1
//   first should be faster (fewer cache misses). This is handy for matrix 
//   multiplication. 
//
//  rows / cols    j = 0,        1,           2,         ...,    dim2
//  i = 0              0,        1,           2,         ...,    dim2
//      1       dim2 + 0, dim2 + 1,    dim2 + 2,         ..., 2x dim2
//      2    2x dim2 + 0, ... 
//      3                       ...
//      4                           ...
//      ...                             ... 
//      dim1                                              dim1 x dim2
//
// ============================================================================
namespace ludwig
{

    template<typename T>
    struct Matrix
    {
        T*  data;
        u32 dim1;
        u32 dim2;
        u64 size;

        Matrix();
        Matrix(u32 d1, u32 d2);
        Matrix(u32 d1, u32 d2, const T  init);
        Matrix(u32 d1, u32 d2, const T* init);
        Matrix(const Matrix<T>& rhs);
        Matrix(Matrix<T>&& rhs) noexcept;

        ~Matrix();

        T& operator[] (const u64 i) noexcept;
        T& operator() (const u32 i, const u32 j = 0) noexcept; 

        const T& operator[] (const u64 i) const noexcept;
        const T& operator() (const u32 i, const u32 j = 0) const noexcept; 
        
        Matrix<T>& operator= (const Matrix<T>& rhs) noexcept;
        Matrix<T>& operator= (Matrix<T>&& rhs) noexcept;

        bool operator== (const Matrix<T>& rhs) const;
        bool operator== (const T& rhs) const;
        
        Matrix<T>& operator+= (const T& rhs);
        Matrix<T>& operator-= (const T& rhs);
        Matrix<T>& operator*= (const T& rhs);
        Matrix<T>& operator+= (const Matrix<T>& rhs);
        Matrix<T>& operator-= (const Matrix<T>& rhs);

        template<typename U> friend Matrix<U> operator+ (const U& lhs, const Matrix<U>& rhs);
        template<typename U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const U& rhs);
        template<typename U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const Matrix<U>& rhs);
    
        template<typename U> friend Matrix<U> operator- (const U& lhs, const Matrix<U>& rhs);
        template<typename U> friend Matrix<U> operator- (const Matrix<U>& lhs, const U& rhs);
        template<typename U> friend Matrix<U> operator- (const Matrix<U>& lhs, const Matrix<U>& rhs);
    
        template<typename U> friend Matrix<U> operator* (const U& lhs, const Matrix<U>& rhs);
        template<typename U> friend Matrix<U> operator* (const Matrix<U>& lhs, const U& rhs);
        template<typename U> friend Matrix<U> operator* (const Matrix<U>& lhs, const Matrix<U>& rhs);

    };
    // ====================================================================== //
    // constructors 
    // ====================================================================== //
    
    template<typename T>
    Matrix<T>::Matrix() : dim1(1), dim2(1), size(1)
    {
        data = new T[size];
        data[0] = static_cast<T>(0.0);
    }

    template<typename T>
    Matrix<T>::Matrix(u32 d1, u32 d2) : dim1(d1), dim2(d2), size(d1*d2)
    {
        data = new T[size];
        memset(data, 0, size*sizeof(*data));
    }

    template<typename T>
    Matrix<T>::Matrix(u32 d1, u32 d2, const T init) : dim1(d1), dim2(d2), size(d1*d2)
    {
        data = new T[size];
        for (u64 i = 0; i < size; i++)
            data[i] = init;
    }

    template<typename T>
    Matrix<T>::Matrix(u32 d1, u32 d2, const T* init) : dim1(d1), dim2(d2), size(d1*d2)
    {
        data = new T[size];
        std::copy(init, init + size, data);
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix<T>& rhs) : dim1(rhs.dim1), dim2(rhs.dim2), size(rhs.size)
    {
        data = new T[size];
        std::copy(rhs.data, rhs.data + rhs.size, data);
    }

    template<typename T>
    Matrix<T>::Matrix(Matrix<T>&& rhs) noexcept : data(nullptr), dim1(0), dim2(0), size(0)
    {
        *this = std::move(rhs);
    }

    template<typename T>
    Matrix<T>::~Matrix()
    {
        if (data != nullptr)
            delete[] data;
    }
    // ====================================================================== //
    // member operator overloads 
    // ====================================================================== //

    template<typename T>
    T& Matrix<T>::operator[] (const u64 i) noexcept
    {
        ASSERT( (i < size), "Array out of bounds: i = %d > size = %d\n", i, size);
        return data[i];
    }

    template<typename T>
    T& Matrix<T>::operator() (const u32 i, const u32 j) noexcept
    {
        ASSERT( (i < dim1),   "Array out of bounds: i = %d > dim1 = %d\n", i, dim1);
        ASSERT( (j < dim2),   "Array out of bounds: j = %d > dim2 = %d\n", j, dim2);
        ASSERT( (j + i * dim2 < size), "Array out of bounds: index = %d > size = %d\n", j+i*dim2, size);
        return data[j + i * dim2];
    }

    template<typename T>
    const T& Matrix<T>::operator[] (const u64 i) const noexcept
    {
        ASSERT( (i < size), "Array out of bounds: i = %d > size = %d\n", i, size);
        return data[i];
    }

    template<typename T>
    const T& Matrix<T>::operator() (const u32 i, const u32 j) const noexcept
    {
        ASSERT( (i < dim1),   "Array out of bounds: i = %d > dim1 = %d\n", i, dim1);
        ASSERT( (j < dim2),   "Array out of bounds: j = %d > dim2 = %d\n", j, dim2);
        ASSERT( (j + i * dim2 < size), "Array out of bounds: index = %d > size = %d\n", j+i*dim2, size);
        return data[j + i * dim2];
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator= (const Matrix<T>& rhs) noexcept
    {
        if ( this != &rhs )
        {
            if (data != nullptr)
                delete[] data;

            dim1 = rhs.dim1;
            dim2 = rhs.dim2;
            size = rhs.size;
            data = new T[size];
            std::copy(rhs.data, rhs.data + size, data);
        }
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator= (Matrix<T>&& rhs) noexcept
    {
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        std::cout << "                   MOVED                          \n";
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        if ( this != &rhs )
        {
            if ( data != nullptr )
                delete[] data;
            
            data = rhs.data;
            dim1 = rhs.dim1;
            dim2 = rhs.dim2;
            size = rhs.size;

            rhs.data = nullptr;
            rhs.dim1 = 0; rhs.dim2 = 0, rhs.size = 0;
        }
        return *this;
    }

    template<typename T>
    bool Matrix<T>::operator== (const Matrix<T>& rhs) const
    {
        if ( (size != rhs.size) || (dim1 != rhs.dim1) || (dim2 != rhs.dim2) )
            return false;
        if ( memcmp(data, rhs.data, size*sizeof(*data)) != 0)
            return false;
        return true;
        
    }

    template<typename T>
    bool Matrix<T>::operator== (const T& rhs) const
    {
        if ( rhs != static_cast<T>(0.0) )
            return false;
        for (u64 i = 0; i < size; i++)
            if ( data[i] != static_cast<T>(0.0) )
                return false;
        return true;
        
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator+= (const T& rhs)
    {
        if ( rhs == static_cast<T>(0.0) )
            return *this;

        for (u64 i = 0; i < size; i++)
            data[i] += rhs;
        return *this;
    }
    
    template<typename T>
    Matrix<T>& Matrix<T>::operator-= (const T& rhs)
    {
        if ( rhs == static_cast<T>(0.0) )
            return *this;

        for (u64 i = 0; i < size; i++)
            data[i] -= rhs;
        return *this;
    }
        
    template<typename T>
    Matrix<T>& Matrix<T>::operator*= (const T& rhs)
    {
        if ( rhs == static_cast<T>(0.0) );
        {
            memset(data, 0, size*sizeof(*data));
            return *this;
        }

        for (u64 i = 0; i < size; i++)
            data[i] *= rhs;
        return  *this;
    }

    // NOTE(chris): these do not check to see if the shape of each matrix is the same
    //              so it is completely valid to add a 2x3 matrix to a 3x2 matrix. 
    //              this is probably undesirable
    template<typename T>
    Matrix<T>& Matrix<T>::operator+= (const Matrix<T>& rhs)
    {
        ASSERT ( (size == rhs.size), "Cannot add two matrices of different size: %d != %d\n", size, rhs.size);
        for (u64 i = 0; i < size; i++)
            data[i] += rhs[i];
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator-= (const Matrix<T>& rhs)
    {
        for (u64 i = 0; i < size; i++)
            data[i] -= rhs.data[i];
        return *this;
    }

    // ====================================================================== //
    // global operator overloads 
    // ====================================================================== //

    template<typename T>
    Matrix<T> operator+ (const T& lhs, const Matrix<T>& rhs) 
    {
        Matrix<T> res(rhs);
        res+=lhs;
        return res;
    }
    
    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& lhs, const T& rhs)
    {
        Matrix<T> res(lhs);
        res+=rhs;
        return res;
    }

    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs)
    {
        Matrix<T> res(lhs);
        res+=rhs;
        return res;
    } 

    template<typename T>
    Matrix<T> operator- (const T& lhs, const Matrix<T>& rhs) 
    {
        Matrix<T> res(rhs);
        res-=lhs;
        return res;
    }
    
    template<typename T>
    Matrix<T> operator- (const Matrix<T>& lhs, const T& rhs)
    {
        Matrix<T> res(lhs);
        res-=rhs;
        return res;
    }

    template<typename T>
    Matrix<T> operator- (const Matrix<T>& lhs, const Matrix<T>& rhs)
    {
        Matrix<T> res(lhs);
        res-=rhs;
        return res;
    } 

    template<typename T>
    Matrix<T> operator* (const T& lhs, const Matrix<T>& rhs)
    {
        Matrix<T> res(rhs);
        res*=lhs;
        return res;
    }

    template<typename T>
    Matrix<T> operator* (const Matrix<T>& lhs, const T& rhs)
    {
        Matrix<T> res(lhs);
        res*=rhs;
        return res;
    }

    template<typename T>
    Matrix<T> operator* (const Matrix<T>& lhs, const Matrix<T>& rhs)
    {
        ASSERT( (lhs.dim2 == rhs.dim1), "cannot multiply %d x %d matrix with %d x %d\n", lhs.dim1, lhs.dim2, rhs.dim1, rhs.dim2);

        Matrix<T> res(lhs.dim1, rhs.dim2);

        for (u32 i = 0; i < lhs.dim1; i++)
            for (u32 j = 0; j < rhs.dim2; j++)
                for (u32 k = 0; k < rhs.dim1; k++)
                    res(i,j) += lhs(i,k) * rhs(k,j);
        return res;
    }

    // ====================================================================== //
    // Matrix operations 
    // ====================================================================== //


    // NOTE(Chris): currently this just masks out the specified column/row to 
    //              yeild the submatrix appropriate for finding the determanent
    template<typename T>
    Matrix<T> SubMatrix(const Matrix<T>& matrix, u32 d1, u32 d2)
    {   
        Matrix<T> subMatrix(matrix.dim1-1, matrix.dim2-1);
        u32 count = 0;
        for (u32 i = 0; i < matrix.dim1; i++)
        {
            for (u32 j = 0; j < matrix.dim2; j++)
            {
                if ( (i != d1) && (j  != d2))
                {
                    subMatrix.data[count] = matrix(i,j);
                    count++;
                }
            }
        }
        return subMatrix;
    }

    template<typename T>
    T Determinant(const Matrix<T>& matrix)
    {
        ASSERT( ( matrix.dim1 == matrix.dim2), "%d x %d matrix is not square - Cannot compute determinant!\n", matrix.dim1, matrix.dim2);
        
        if ( matrix.dim1 == 2)
            return matrix(0,0) * matrix(1,1) - matrix(0,1) * matrix(1,0);
        
        T determinant = 0.0;
        T sign = 1.0;
        
        for (u32 j = 0; j < matrix.dim2; j++)
        {
            Matrix<T> subMatrix = SubMatrix(matrix, 0, j);
            determinant += matrix(0,j) * Determinant<T>(subMatrix) * sign;
            sign *= -1;
        }
        
        return determinant;
    }

    template<typename T>
    Matrix<T> Inverse(const Matrix<T>& matrix)
    {
        

    }
    
    template<typename T>
    bool Compare (const Matrix<T>& lhs, const Matrix<T>& rhs, f64 tolerance)
    {

        return true;

    }
    
    template<typename T>
    Matrix<T> IdentityMatrix(u32 dim)
    {
    
        Matrix<T> matrix(dim, dim);
        for (u32 i = 0; i < dim; i++)
            for (u32 j = 0; j < dim; j++)
                if ( i == j )
                    matrix(i,j) = 1.0;
        return matrix;
    }

    template<typename T>
    Matrix<T> IdentityMatrix(Matrix<T>& matrix)
    {
        ASSERT( (matrix.dim1 == matrix.dim2), "Cannot convert a %d x %d matrix to the Identity - It is not square!\n", matrix.dim1, matrix.dim2);


        memset(matrix.data, 0, matrix.size*sizeof(*matrix.data));
    
        for (u32 i = 0; i < matrix.dim1; i++)
            for (u32 j = 0; j < matrix.dim2; j++)
                if ( i == j )
                    matrix(i,j) = 1.0;
        return matrix;
    }
}
