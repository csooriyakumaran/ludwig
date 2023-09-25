#pragma once

#include <vector>


namespace ludwig
{

    template<typename T>
    std::vector<T> linspace(T start, T end, uint64_t n)
    {
        std::vector<T> res(n);
        
        if (n <= 0)
            return res;
        
        T delta = (end - start) / ( n - 1 ); 
             
        for (uint64_t i = 0; i < res.size(); i++)
            res[i] = start + delta * i;
        
        return res;
    }
}
