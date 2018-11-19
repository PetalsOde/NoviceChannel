#include "boost/multi_array.hpp"
#include "test.h"

int main ()
{
        int  I_LATS, I_LONS, I_LVLS, I_RECS;
        I_LATS = 73, I_LONS = 144 , I_LVLS = 17, I_RECS = 1460 ;

  // Create a 4D array

  typedef boost::multi_array<double, 4> array_type;
  typedef array_type::index index;
  array_type A(boost::extents[I_RECS][I_LVLS][I_LATS][I_LONS]);
  Assign_Data ad;
  ad.assign_data(A, I_RECS, I_LVLS, I_LATS, I_LONS );

 // PRINT DATA TO VARIFY
                for (int i = 0 ; i < 5 ; i++ )
                        for (int j = 0 ; j < 5 ; j++ )
                        for (int k = 0 ; k < 5 ; k++ )
                        for (int l = 0 ; l < 5 ; l++ )
                        {
                                std::cout<<"arr["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"] =  "<<A[i][j][k][l] << '\n' ;
                        }
  return 0;
}
