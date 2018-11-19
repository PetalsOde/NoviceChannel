#include "test.h"

void Assign_Data::assign_data(boost::multi_array<double, 4> &arr, int &nx, int &ny, int &nz, int &nt )
                {
                        int values1 = 0;
                        for (int i = 0 ; i < nx ; i++ )
                        for (int j = 0 ; j < ny ; j++ )
                        for (int k = 0 ; k < nz ; k++ )
                        for (int l = 0 ; l < nt ; l++ )
                        {
                                arr[i][j][k][l] = values1++;

                        //      std::cout<<"arr["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"] =  "<<arr[i][j][k][l] << '\n' ;
                        }
                }
~
