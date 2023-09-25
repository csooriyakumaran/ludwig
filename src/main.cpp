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

        for (u32 j = 1; j < jmax; j++)
             v(0, j) = v(0,j-1) - dy[j-1]*((u(0,j)/Ue[0])*(Ue[1] - Ue[0])/deltax - y[j]/del1[0]*(del1[1]-del1[0])/deltax*(u(0,j) - u(0,j-1) )/dy[j-1]);

        for (u32 i = 0; i < imax; i++)
        {
            for (u32 j = 0; j < jmax; j++)
                std::cout << std::setw(10) << v(i,j) << '\t';
            std::cout << "\n";
        }


    
        for (uint32_t i = 0; i < imax-1; i++)
        {
            Mat2<f64> A(jmax-2, jmax-2, 0);
            std::vector<f64> b(jmax-2, 0);
            
            u32 k = 0;
            for (uint32_t j = 1; j < jmax-1; j++)
            {
                f64 alpha = ( viscosity / density ) / u(i,j) * ( deltax / (dy[j-1]*dy[j-1]) );
                f64 beta  = v(i,j) / u(i,j) * deltax / ( dy[j] + dy[j-1]);

                if ( j == 1)
                {

                    A(k,k)   = 1.0l + 2.0l * alpha;
                    A(k,k+1) = -alpha;
                    b[k]     =  alpha*u(i+1,j-1) + u(i,j) - beta * (u(i,j+1) - u(i,j-1)) + (Ue[i+1]*Ue[i+1] - Ue[i]*Ue[i]) / (2. * u(i,j) );

                } else if (j == jmax-2) {
                
                    A(k,k-1) = -alpha;
                    A(k,k)   = 1.0l + 2.0l * alpha;
                    b[k]     = alpha*u(i+1,j+1) + u(i,j) - beta * ( u(i,j+1) - u(i,j-1)) + (Ue[i+1]*Ue[i+1] - Ue[i]*Ue[i]) / (2. * u(i,j));
                } else {
                    A(k,k-1) = -alpha;
                    A(k,k)   = 1.0l + 2.0l * alpha;
                    A(k,k+1) = -alpha;
                    b[k]     = u(i,j) - beta * ( u(i,j+1) - u(i,j-1) ) + (Ue[i+1]*Ue[i+1] - Ue[i]*Ue[i]) / (2. * u(i,j));
                }
                k++;    
            }
            for (uint32_t i = 0; i < imax; i++)
            {
                for (uint32_t j = 0; j < jmax; j++)
                    std::cout << std::setprecision(8) << A(i,j) << "\t";

                std::cout << std::endl;
            }
        }
        

    }
}


int main(int argc, char** argv)
{
    ludwig::run();
    
    return 0;
}

