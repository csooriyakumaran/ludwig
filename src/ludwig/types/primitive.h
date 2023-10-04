#pragma once

#include <stdint.h>
#include <complex>

namespace ludwig
{
    typedef uint8_t       u8;
    typedef int8_t        i8;
    
    typedef uint16_t     u16;
    typedef int16_t      i16;
    
    typedef uint32_t     u32;
    typedef int32_t      i32;

    typedef uint64_t     u64;
    typedef int64_t      i64;

    typedef double       f64;
    typedef float        f32;
    typedef long double f128; // compiler specific, may not be 128 bit, sometimes is 80 bit

    typedef std::complex<f64>  c64;
    typedef std::complex<f32>  c32;
    typedef std::complex<f128> c128;

}
