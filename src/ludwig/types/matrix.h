#pragma once
#include "primitive.h"

#include <cstring>

// =========================== MATRICES =======================================
// - these are algebreaic matrices which follow typical matrix arithematic 
//   rules. Matrix1 is a single column matrix (i.e., it is an algebreaic 
//   vector, which is not the same as a vector from above)
//
//  rows / cols    j = 0,       1,           2,         ..., dim2
//  i = 0              0     dim1 + 0    2*dim1 + 0
//      1              1     dim1 + 1    2*dim1 + 1
//      2              2
//      3              3
//      4              4
//      ...            ...
//      dim1           dim1  dim1+dim1     3* dim1
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

        Matrix() : dim1(1), dim2(1), size(1)
        {
            data = new T[size];
            data[0] = 0.0;
        }
            
        Matrix(u32 d1, u32 d2) : dim1(d1), dim2(d2), size(d1*d2)
        {
            data = new T[size];
            memset(data, 0, size*sizeof(*data));
        }

        Matrix(u32 d1, u32 d2, const T init) : dim1(d1), dim2(d2), size(d1*d2)
        {
            data = new T[size];
            for (u64 i = 0; i < size; i++)
                data[i] = init;
        }

        Matrix(u32 d1, u32 d2, const T* init) : dim1(d1), dim2(d2), size(d1*d2)
        {
            data = new T[size];
            memcpy(data, init, size*sizeof(*data));
        }

        Matrix(const Matrix<T>& rhs)
        {
            dim1 = rhs.dim1;
            dim2 = rhs.dim2;
            size = rhs.size;
            
            data = new T[size];
            memcpy(data, rhs.data, size*sizeof(*data));
        }

        ~Matrix()
        {
            if (data != nullptr)
                delete[] data;
        }

        // one-dimensional flat access (read/write)
        T& operator[] (const u64 i)
        {
            return data[i];
        }

        // one-dimensional flat access (read)
        const T& operator[] (const u64 i) const
        {
            return data[i];
        }

        // two-dimensional indexed access (read/write)
        T& operator() (const u32 i, const u32 j = 0)
        {
            return data[i + j * dim1];
        }

        // two-dimensional indexed access (read)
        const T& operator() (const u32 i, const u32 j = 0) const
        {
            return data[i + j * dim1];
        }
        
        Matrix<T>& operator= (const Matrix<T> rhs)
        {
            dim1 = rhs.dim1;
            dim2 = rhs.dim2;
            size = rhs.size;
            if (data != nullptr)
                delete[] data;
            
            data = new T[size];
            memcpy(data, rhs.data, size*sizeof(*data));
            return *this;
        }

        bool operator== (const Matrix<T>& rhs) const
        {
            if ( (size != rhs.size) || (dim1 != rhs.dim1) || (dim2 != rhs.dim2) )
                return false;
            if ( memcmp(data, rhs.data, size*sizeof(*data)) != 0)
                return false;
            return true;
            
        }
        
        Matrix<T> operator+= (const Matrix<T>& rhs)
        {
            for (u64 i = 0; i < size; i++)
                data[i] += rhs.data[i];
            return *this;
        }
        
        Matrix<T> operator+= (const T& rhs)
        {
            for (u64 i = 0; i < size; i++)
                data[i] += rhs;
            return *this;
        }
    
        Matrix<T> operator-= (const Matrix<T>& rhs)
        {
            for (u64 i = 0; i < size; i++)
                data[i] -= rhs.data[i];
            return *this;
        }
        
        Matrix<T> operator-= (const T& rhs)
        {
            for (u64 i = 0; i < size; i++)
                data[i] -= rhs;
            return *this;
        }
        
        Matrix<T> operator*= (const T& rhs)
        {
            for (u64 i = 0; i < size; i++)
                data[i] *= rhs;
            return  *this;
        }

        // NOTE(Chris): currently this just masks out the specified column/row to 
        //              yeild the submatrix appropriate for finding the determanent
        Matrix<T> SubMatrix(u32 d1, u32 d2)
        {   
            Matrix<T> subMatrix(dim1-1, dim2-1);
            u32 count = 0;
            for (u32 j = 0; j < dim2; j++)
            {
                for (u32 i = 0; i < dim1; i++)
                {
                    if ( (i != d1) && (j  != d2))
                    {
                        subMatrix.data[count] = data[i + j * dim1];
                        count++;
                    }
                }
            }
            return subMatrix;
        }

        template<typename U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const Matrix<U>& rhs);
        template<typename U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const U& rhs);
        template<typename U> friend Matrix<U> operator+ (const U& lhs, const Matrix<U>& rhs);
    
        template<typename U> friend Matrix<U> operator- (const Matrix<U>& lhs, const Matrix<U>& rhs);
        template<typename U> friend Matrix<U> operator- (const Matrix<U>& lhs, const U& rhs);
        template<typename U> friend Matrix<U> operator- (const U& lhs, const Matrix<U>& rhs);
    
        template<typename U> friend Matrix<U> operator* (const Matrix<U>& lhs, const Matrix<U>& rhs);
        template<typename U> friend Matrix<U> operator* (const Matrix<U>& lhs, const U& rhs);
        template<typename U> friend Matrix<U> operator* (const U& lhs, const Matrix<U>& rhs);

    };
        
    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs)
    {
        Matrix<T> res(lhs);
        res+=rhs;
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
    Matrix<T> operator+ (const T& lhs, const Matrix<T>& rhs) 
    {
        Matrix<T> res(rhs);
        res+=lhs;
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
    Matrix<T> operator- (const Matrix<T>& lhs, const T& rhs)
    {
        Matrix<T> res(lhs);
        res-=rhs;
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
    Matrix<T> operator* (const Matrix<T>& lhs, const Matrix<T>& rhs)
    {
        Matrix<T> res(lhs.dim1, rhs.dim2);
        
        for (u32 i = 0; i < lhs.dim1; i++)
            for (u32 j = 0; j < rhs.di1; j++)
                for (u32 k = 0; k < lhs.dim2; k++)
                    res(i,j) += lhs(i,k) * rhs(k,j);
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
    Matrix<T> operator* (const T& lhs, const Matrix<T>& rhs)
    {
        Matrix<T> res(rhs);
        res*=lhs;
        return res;
    }

    template<typename T>
    T Determinant(const Matrix<T> matrix)
    {
        if ( matrix.dim1 != matrix.dim2)
            throw std::invalid_argument("Cannot compute the determinant of a matrix that is not square.");
        
        if ( matrix.dim1 == 2)
            return matrix(0,0) * matrix(1,1) - matrix(0,1) * matrix(1,0);
        
        T determinant = 0.0;
        T sign = 1.0;
        
        for (u32 j = 0; j < matrix.dim2; j++)
        {
            Matrix<T> subMatrix = matrix.SubMatrix(0,j);
            determinant += matrix(0,j) * Determinant<T>(subMatrix) * sign;
            sign *= -1;
        }
        
        return determinant;
    }

}
