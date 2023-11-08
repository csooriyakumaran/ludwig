#include "temp.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>


#include "ludwig/mesh/geometry.h"
#include "ludwig/mesh/uniform-grid.h"
#include "ludwig/solver/tdma.h"
#include "ludwig/flow/flowfield.h"
#ifdef DEBUG
    #include "tests/test-matrix.h"
    #include "tests/test-vector.h"
    #include "tests/test-arrays.h"
#endif

#include "cgnslib.h"

namespace ludwig
{

    void run()
    {
        std::cout << "TEST\n";
        f64 density = 1.182;
        f64 viscosity = 1.83e-5;
        f64 U0 = 1.0;


        // geom --> move to a geometry structure
        f64 plate_length = 0.2;
        f64 xmin = 0.005*plate_length;
        f64 xmax = 0.13*plate_length;

        f64 ymin = 0.0;
        f64 ymax = 0.02*plate_length;
        
        // geom  = { {xmin, ymin), (xmax, ymin), (xmax, ymax), (xmin, ymax) }
        
        // grid -> move to a mesh structure ... how to handle boundary conditions? Generally or specific for this case?
        // mesh = HexMesh(geom, inflation_rate, ni, nj, nk=1) 
        uint32_t imax = 10;
        uint32_t jmax = 100;
        f64 deltax = ( xmax - xmin ) / ( imax - 1 );
        f64 deltay = ( ymax - ymin ) / ( jmax - 1 );

        // for now just assume uniform grid
        Vector<f64> x = vk::linspace(xmin, xmax, imax);
        Vector<f64> y = vk::linspace(ymin, ymax, jmax);     

        std::vector<f64> dx(imax-1, deltax);
        std::vector<f64> dy(jmax-1, deltay);
        
        // flowfield(mesh)
        Matrix<f64> u(imax, jmax, 0.0);
        Matrix<f64> v(imax, jmax, 0.0);
        
        std::vector<f64> Ue(imax);
        std::vector<f64> Re(imax);
        std::vector<f64> del1(imax);

        for (u32 i = 0; i < imax; i++)
        {
            Ue[i] = U0 * ( 1 - x[i]/plate_length );
            Re[i] = Ue[i] * x[i] * density/viscosity;
            del1[i] = 5.0 * x[i] / pow(Re[i], 0.5);
            u(i, jmax-1) = Ue[i];
        }
        
        // initial conditions
        for (u32 j = 1; j < jmax-1; j++)
        {
            if ( y[j] >= del1[0] )
                u(0, j) = Ue[0];
            else
                u(0, j) = Ue[0] * pow((y[j] / del1[0]),0.5);
        }

        for (u32 j = 1; j < jmax; j++)
             v(0, j) = v(0,j-1) - dy[j-1]*((u(0,j)/Ue[0])*(Ue[1] - Ue[0])/deltax - y[j]/del1[0]*(del1[1]-del1[0])/deltax*(u(0,j) - u(0,j-1) )/dy[j-1]);

        for (u32 i = 0; i < imax; i++)
        {
            for (u32 j = 0; j < jmax; j++)
                std::cout << std::setw(10) << v(i,j) << '\t';
            std::cout << "\n";
        }

        // Flowfield.solve( solverfn-> Crank_Nicolson)
        for (uint32_t i = 0; i < imax-1; i++)
        {
            Matrix<f64> A(jmax-2, jmax-2);
            Vector<f64> b(jmax-2);
            Vector<f64> c(jmax-2);

            u32 k = 0;
            for (u32 j = 1; j < jmax-1; j++)
            {
                f64 alpha = ( viscosity / density ) / u(i,j) * ( deltax / (dy[j-1]*dy[j-1]) );
                f64 beta  = v(i,j) / u(i,j) * deltax / ( dy[j] + dy[j-1]);

                if ( j == 1)
                {
                    A(k,k)   = 1.0l + 2.0l * alpha;
                    A(k,k+1) = -alpha;
                    b(k)     =  alpha*u(i+1,j-1) + u(i,j) - beta * (u(i,j+1) - u(i,j-1)) + (Ue[i+1]*Ue[i+1] - Ue[i]*Ue[i]) / (2. * u(i,j) );
                } else if (j == jmax-2) {
                    A(k,k-1) = -alpha;
                    A(k,k)   = 1.0l + 2.0l * alpha;
                    b(k)     = alpha*u(i+1,j+1) + u(i,j) - beta * ( u(i,j+1) - u(i,j-1)) + (Ue[i+1]*Ue[i+1] - Ue[i]*Ue[i]) / (2. * u(i,j));
                } else {
                    A(k,k-1) = -alpha;
                    A(k,k)   = 1.0l + 2.0l * alpha;
                    A(k,k+1) = -alpha;
                    b(k)     = u(i,j) - beta * ( u(i,j+1) - u(i,j-1) ) + (Ue[i+1]*Ue[i+1] - Ue[i]*Ue[i]) / (2. * u(i,j));
                }
                k++;
            }
             solve::TDMA<f64>(A, b, c);
            
            // TODO(chris): replace detlay with dy[index] and double check the appropriate index to be used
            for (u32 j=0; j < jmax-2; j++)
            {
                u(i+1, j+1) = c(j);
                v(i+1, j+1) = v(i+1, j) - deltay / (2.0l*deltax) * ( u(i+1, j+1) - u(i+1, j+1) + u(i+1, j) - u(i, j) );
            }

        }

        // for (uint32_t i = 0; i < imax; i++)
        // {
        //     for (uint32_t j = 0; j < jmax; j++)
        //         std::cout << std::setprecision(8) << u(i,j) << "\t";

        //     std::cout << std::endl;
        // }

        for (u32 i = 0; i < imax; i++)
        {
            for (u32 j = 0; j < jmax; j++)
                std::cout << std::setprecision(8) << u(i,j) << "\t";
            std::cout << "\n";
        }
    }

}

template<typename T>
auto timeit(size_t iterations, std::function<void()> func)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < iterations; i++)
        func();
    auto stop  = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<T>(stop - start) / iterations;
}

int dep_main(int argc, char** argv)
{
    ludwig::VectorField f(4,2,3);
    for (uint64_t i = 0; i < f.size; i++)
        std::cout << f[i] << "\n"; 
    return 0;
    // auto dur = timeit<std::chrono::nanoseconds>(1, []() { ludwig::Matrix<ludwig::f64>  A(100000, 10000, 1.23455); ludwig::f64 B = A[1000]; });

#ifdef DEBUG
    ludwig::test::test_matrix();
    ludwig::test::test_arrays();
    ludwig::test::test_vector();
#endif
    auto dur = timeit<std::chrono::microseconds>(100, []() { ludwig::run(); });
    std::cout << dur << "\n";
    return 0;
}

