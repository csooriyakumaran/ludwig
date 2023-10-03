#pragma once

#include <iostream>
#include <iomanip>

#include "../ludwig/types/vector.h"

namespace ludwig::test
{
    static void test_Vec2()
    {
        { // assignment
            Vec2<u32> v0;
            std::cout << " >> Vec2<u32> v0; -> " << v0 << "\n";
            v0 = static_cast<Vec2<u32>>(1);
            std::cout << " >> v0 = static_cast<Vec2<u32>>(1); -> " << v0 << "\n";
            v0 = Vec2<u32>(2);
            std::cout << " >> v0 = Vec2(2); -> " << v0 << "\n"; 
        }   
        { // arithmatic
            Vec2<u32> v1(1);
            std::cout << "Vec2<u32> v1(1); -> " << v1 << "\n";
        }   
        { // dot, magnitude, angle

        }
        Vec2<f64> v1 = {1.2,2.3};
        std::cout << "Vec2<f64> v1 = {1.2,2.3}; -> " << v1 << "\n";
        Vec2<f64> v2(4.2,5.3);
        Vec2<f64> v3 = v1 + v2;
        std::cout << v3.x << " " << v3.y << std::endl;
        v3 = static_cast<Vec2<f64>>(0.0);
        std::cout << v3 << "\n";
    }

    static void test_Vec3()
    {

        Vector<u32> vdims({1,2,3});
        for (u64 i = 0; i < vdims.size; i++)
            std::cout << "vdims[" << i <<"] = " << vdims[i] << "\n";
        
        Vec3<f64> vec1 = {1.0, 2.0, 3.0};
        Vec3<f64> vec2 = {4.0, 5.0, 6.0};
        f64 dotResult = vectorDotProduct(vec1, vec2);
        Vec3<f64> crossResult = vectorCrossProduct(vec1, vec2);
        f64 angle = vectorAngle(vec1, vec2);
        std::cout << "Cross Product: " << crossResult << "\n";
        std::cout << "Dot Product: " << dotResult << std::endl;
        std::cout << "Angle between: " << angle << std::endl;
    }

    static void test_Vec4()
    {
    }

    static void test_Vector()
    {
    }

    static void test_vector()
    {
        std::cout << " ===== TEST VECTORS ===== \n"; 
        test_Vec2();
        test_Vec3();
        test_Vec4();
        test_Vector();
    }
}
