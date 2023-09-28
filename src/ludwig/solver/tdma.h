#include "../types/types.h"

namespace ludwig
{
    // TODO(chris): change indexing for maxtrix to use [i,j] instead of (i,j) to maintain consistency with std::vector
    template<typename T>
    void SolveTDMA(Matrix<T> A, Matrix<T> b, Matrix<T>& x)
    {
        uint32_t m = b.size;
        
        std::cout << b.size << std::endl;
        std::cout << x.size << std::endl;

        // first row coefficients
        A(0,1) = A(0, 1) / A(0,0);
        b(0)   = b(0) / A(0,0);

        // forward elimination
        for ( int i = 1; i < m-1; i++)
        {
            T d = A(i,i) - A(i-1, i) * A(i, i-1);
            A(i, i+1) = A(i, i+1) / d;
            b(i)      = ( b(i)- A(i, i-1)*b(i-1) ) / d;
        }

        // last row
        x(m-1) = ( b(m-1) - A(m-1, m-2) * b(m-2) ) / ( A(m-1, m-1) - A(m-2,m-1)*A(m-1, m-2) );

        for (int i = m-2; i >= 0; i--)
            x(i) = -A(i, i+1)*x(i+1) + b(i);
    }

}
