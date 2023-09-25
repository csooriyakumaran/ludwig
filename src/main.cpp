#include <iostream>
#include <iomanip>
#include "ludwig/core/types.h"
#include "ludwig/core/linspace.h"
#include "ludwig/mesh/uniform-grid.h"


namespace ludwig
{

    void run()
    {

        f64 plate_length = 0.2l;
        f64 U0 = 1.0l;
        f64 density = 1.182l;
        f64 viscosity = 1.83e-5;

        f64 xmin = 0.005*plate_length;
        f64 xmax = 0.13*plate_length;
        uint32_t imax = 10;

        f64 ymin = 0.0l;
        f64 ymax = 0.02*plate_length;
        uint32_t jmax = 10;
        
        f64 deltax = ( xmax - xmin ) / ( imax - 1 );
        f64 deltay = ( ymax - ymin ) / ( jmax - 1 );
 
        // for now just assume uniform grid
        std::vector<f64> x = linspace(xmin, xmax, imax);
        std::vector<f64> y = linspace(ymin, ymax, jmax);     
  
        for (auto el : y)
            std::cout << el << "\n";

        std::vector<f64> dx(imax-1, deltax);
        std::vector<f64> dy(jmax-1, deltay);
    
        std::cout << ymax <<std::endl;

        Mat2<f64> u(imax, jmax, 0.0l);
        Mat2<f64> v(imax, jmax, 0.0l);
        
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

        for (u32 j = 1; j < jmax-1; j++)
             v(0, j) = v(0,j-1) - dy[j-1]*((u(0,j)/Ue[0])*(Ue[1] - Ue[0])/deltax - y[j]/del1[0]*(del1[1]-del1[0])/deltax*(u(0,j) - u(0,j-1) )/dy[j-1]);

        for (u32 i = 0; i < imax; i++)
        {
            for (u32 j = 0; j < jmax; j++)
                std::cout << std::setw(10) << u(i,j) << '\t';
            std::cout << "\n";
        }

        uint32_t cols = 10;
        uint32_t rows = 10;

        Mat2<f64> A(rows, cols);
        A(0,1) = 1.0l;
        for (uint32_t i = 0; i < rows; i++)
        {
            for (uint32_t j = 0; j < rows; j++)
                A(i,j) = 1.1l*(i+j);
        }
        
        for (uint32_t i = 0; i < rows; i++)
        {
            for (uint32_t j = 0; j < rows; j++)
                std::cout << A(i,j) << "\t";

            std::cout << std::endl;
        }

    }
}


int main(int argc, char** argv)
{
    ludwig::run();
    
    return 0;
}

