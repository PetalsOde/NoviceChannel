#include "boost/multi_array.hpp"
#include <cassert>

void assign_data(boost::multi_array<double, 3> &arr, int &nx, int &ny, int &nz )
{
        int values1 = 0;
        for (int i = 0 ; i < nx ; i++ )
        for (int j = 0 ; j < ny ; j++ )
        for (int k = 0 ; k < nz ; k++ )
        {
                arr[i][j][k] = values1++;

                std::cout<<"arr["<<i<<"]["<<j<<"]["<<k<<"] =  "<<arr[i][j][k] << '\n' ;
        }
}



int main ()
{
        int  I_LATS, I_LONS, I_LVLS;
  I_LATS = 5, I_LONS = 5 , I_LVLS = 5 ;

  // Create a 3D array that is 3 x 4 x 2
  typedef boost::multi_array<double, 3> array_type;
  typedef array_type::index index;
  array_type A(boost::extents[I_LVLS][I_LATS][I_LONS]);

  assign_data(A, I_LATS, I_LONS, I_LVLS );

 // PRINT DATA TO VARIFY
        for (int i = 0 ; i < I_LVLS ; i++ )
        for (int j = 0 ; j < I_LATS ; j++ )
        for (int k = 0 ; k < I_LONS ; k++ )
        {
                std::cout<<"a["<<i<<"]["<<j<<"]["<<k<<"] =  "<<A[i][j][k] << '\n' ;
        }
  return 0;
}
