#pragma once

#include "primitive.h"

namespace ludwig
{
    // =========================== VECTORS =================================
    // - these are mathematical vectros with n singl-element components
    template<typename T>
    struct Vector2
    {
        T x;
        T y;
    };

    template<typename T>
    struct Vector3
    {
        T x;
        T y;
        T z;
    };


    template<typename T>
    struct Vector4
    {
        T x;
        T y;
        T z;
        T w;

    };

}
