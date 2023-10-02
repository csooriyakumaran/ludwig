#pragma once

#include <iostream>
#include <iomanip>

#include "ludwig/types/types.h"


namespace ludwig
{

    static void print_array_zy(Array3<f64>& A, u32 i)
    {
        std::cout << "-------------------==== i : "<< i << " ====-------------------\n";
        std::cout << std::setw(8) << "k : " << "     |";
        for (u32 k = 0; k < A.nk; k++)
            std::cout << std::setw(8) << k;
        std::cout << "\n";
        std::cout << "-----------------------------------------------------\n";
        std::cout << "\n";
        for (u32  j= 0; j < A.nj; j++)
        {
            std::cout << std::setw(8) << "j : " << std::setw(4) << j << " |";
            for (u32 k = 0; k < A.nk; k++)
                std::cout << std::setw(8) << A.data[i + j*A.ni + k*A.ni*A.nj];
            std::cout << "\n";
        }
        std::cout << "-----------------------------------------------------\n";

    }
    static void print_array(Array3<f64>& A, const char* name)
    {
        std::cout << "=================   " << std::setw(13) << name;
        std::cout << "   =================" << "\n"; 
        std::cout << " Size: " << A.size << ", Shape: " << A.ni << " x " << A.nj << " x " << A.nk << "\n";
        for (u32 i = 0; i < A.ni; i++)
            print_array_zy(A, i);

        std::cout << "Memory Layout: ";
        for (u64 i = 0; i < A.size; i++)
            std::cout << std::fixed << std::setprecision(3) << std::setw(8) << A.data[i];
        std::cout << "\n";
        std::cout << "=====================================================\n";

    }

    static void test_array_all()
    {
        f64 data[24];
        for (int i = 0; i < 24; i++)
            data[i] = (f64)i;
        Array3<f64> A(4,3,2, data);
        print_array(A, "A     ");
        Array3<f64> B = A.slice(0, A.ni, 0, A.nj, 0, 1);
        print_array(B, "B = A.slice()");
        u32 dims[3] = {4,3,2};
        Vector<u32> vdims({1,2,3});
        for (u64 i = 0; i < vdims.size; i++)
            std::cout << "vdims[" << i <<"] = " << vdims[i] << "\n";
        
        Vec2<f64> v1 = {1.2,2.3};
        Vec2<f64> v2 = {4.2,5.3};
        Vec2<f64> v3 = v1 + v2;
        std::cout << v3.x << " " << v3.y << std::endl;
    }
}
