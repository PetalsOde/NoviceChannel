#include <string>
#include <iostream>
#include "QuatDpointer.h"


int main()
{
        size_t NT, NZ,NY, NX ;

        float ****p = new float ***[NT];
    for(int i = 0; i < NT; i++)
    {
        p[i] = new float **[NZ];
        for(int j = 0; j < NZ; j++)
                {
                        p[i][j] = new float *[NY];
                        for(int k =0; k < NY; k++)
                        {
                                p[i][j][k] = new float [NX];
                        }
                }

    }

        float* zpos = NULL;
        zpos = new float[NZ];
        float* ypos = NULL;
        ypos = new float[NY];
        float* xpos = NULL;
        xpos = new float[NX];
        std:: cout<<"1D array dynamic formed "<< std:: endl;
        double tpos[1500];

        QuatDpointer shp;
        shp.data_read( NT, NZ, NY, NX, p );

        for (int i =0; i < 2 ; i++)
        for (int j =0; j < 5 ; j++)
        for (int k = 0 ; k < 5 ; k++)
        for (int l = 0 ; l < 5 ; l++ )
        {
                std::cout << p[i][j][k][l] <<std::endl;

        }
        std::cout<< "NT  " <<NT <<std::endl;
        std::cout<< "NZ  " <<NZ <<std::endl;
        std::cout<< "NY  " <<NY <<std::endl;
        std::cout<< "NX  " <<NX <<std::endl;

        return 0;

}
