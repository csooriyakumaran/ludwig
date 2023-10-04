#pragma once

#include <iostream>
#include <iomanip>

#include "ludwig/types/types.h"


namespace ludwig::test
{

    static void print_array_xy(Array3<f64>& A, u32 k)
    {
        std::cout << "-------------------==== k : "<< k << " ====-------------------\n";
        std::cout << std::setw(8) << "j : " << "     |";
        for (u32 j = 0; j < A.nj; j++)
            std::cout << std::setw(8) << j;
        std::cout << "\n";
        std::cout << "-----------------------------------------------------\n";
        for (u32  i= 0; i < A.ni; i++)
        {
            std::cout << std::setw(8) << "i : " << std::setw(4) << i << " |";
            for (u32 j = 0; j < A.nj; j++)
                std::cout << std::setw(8) << A(i,j,k);
            std::cout << "\n";
        }
        std::cout << "-----------------------------------------------------\n";

    }
    static void print_array(Array3<f64>& A, const char* name)
    {
        std::cout << "=================   " << std::setw(13) << name;
        std::cout << "   =================" << "\n"; 
        std::cout << " Size: " << A.size << ", Shape: " << A.ni << " x " << A.nj << " x " << A.nk << "\n";
        for (u32 k = 0; k < A.nk; k++)
            print_array_xy(A, k);

        std::cout << "Memory Layout: ";
        for (u64 i = 0; i < A.size; i++)
            std::cout << std::fixed << std::setprecision(3) << std::setw(8) << A.data[i];
        std::cout << "\n";
        std::cout << "=====================================================\n";

    }

    static void test_array_constructions()
    {
        std::cout << "===== Arr2 Construction ===== \n";
        { // Array3<T>::Array3() 
            Array3<f64> a0;
            print_array(a0, " Array3<f64> a0;");
        }

        { // Arr3<T>::Arr3(const u32, const u32, const 32)
            Array3<f64> a0(4,3,2);
            print_array(a0, " Array3<f64> a0;");
            a0.emplace_x({1,2,3,4}, 0, 0);
            print_array(a0, " Array3<f64> a0;");
            a0.emplace_y({4,8,12}, 2, 1);
            print_array(a0, " Array3<f64> a0;");
            a0.emplace_z({3.4,6.8}, 1, 2);
            print_array(a0, " Array3<f64> a0;");
        }

        {
        }
            Array<f64> A(4,3,4);
            for (u32 i = 0; i < A.dims.x; i++)
                for (u32 j = 0; j < A.dims.y; j++)
                    for (u32 k = 0; k < A.dims.z; k++)
                            A(i,j,k) = i + j * A.dims.x + k * A.dims.x * A.dims.y;
            
            printf("Array is %dx%dx%dx%d array of size %d\n", A.dims.x, A.dims.y, A.dims.z, A.dims.t, A.size);
            for (u32 t = 0; t < A.dims.t; t++)
                for (u32 k = 0; k < A.dims.z; k++)
                    for (u32 j = 0; j < A.dims.y; j++)
                        for (u32 i = 0; i < A.dims.x; i++)
                            printf("A(%d,%d,%d,%d) = %.4f\n", i, j, k, t, A(i,j,k,t));
        {

        }

        {

        }

        {

        }

    }
    
    static void test_array_slicing()
    {
        f64 data[24];
        for (int i = 0; i < 24; i++)
            data[i] = (f64)i;
        Array3<f64> A(4,3,2, data);
        print_array(A, "A     ");
        Array3<f64> B = A.slice(0, A.ni, 0, A.nj, 1, 1);
        print_array(B, "B = A.slice()");

    }

    static void test_arrays()
    {
        ludwig::test::test_array_constructions();
        ludwig::test::test_array_slicing();
    }
}


