#include "QuatDpointer.h"


QuatDpointer::QuatDpointer()
{
}

void QuatDpointer::data_read(size_t &nt, size_t &nz, size_t &ny, size_t &nx, float ****var )
{
        std::cout<<"Enter the values for the  nt, nz, ny, nx " <<std::endl;
        std::cin>> nt ;
        std::cin>> nz ;
        std::cin>> ny ;
        std::cin>> nx ;


//      float ****p = *var;

        for (int i = 0 ; i < nt ; i++)
        for (int j = 0 ; j < nz ; j++)
        for (int k = 0 ; k < ny ; k++)
        for (int l = 0 ; l < nx ; l++)
        {
                var[i][j][k][l] = (float) (i) * (j) * (k) * (l) ;

        }


}
