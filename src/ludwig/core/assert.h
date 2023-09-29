#pragma once

#ifdef PLATFORM_WINDOWS
    #define DEBUG_BREAK __debugbreak()
#else
    #define DEBUG_BREAK
#endif

#ifdef DEBUG
    #define ENABLE_ASSERTS
#endif

#ifdef ENABLE_ASSERTS
    #define ASSERT_MESSEGE_INTERNAL(...) printf("\nERROR :: " __VA_ARGS__)
    #define ASSERT(condition, ...) { if(!(condition)) { ASSERT_MESSEGE_INTERNAL(__VA_ARGS__); DEBUG_BREAK; } }
#else
    #define ASSERT_MESSEGE_INTERNAL(...)
    #define ASSERT(condition, ...)
#endif
