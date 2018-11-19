#include "boost/multi_array.hpp"
#include <cassert>

int
main () {

  int  I_LATS, I_LONS, I_LVLS;
  I_LATS = 5, I_LONS = 5 , I_LVLS = 5 ;
  typedef boost::multi_array<double, 3> array_type;
  typedef array_type::index index;
  array_type A(boost::extents[I_LVLS][I_LATS][I_LONS]);

  int values = 0;
  for(index i = 0; i != 3; ++i)
    for(index j = 0; j != 4; ++j)
      for(index k = 0; k != 2; ++k)
        A[i][j][k] = values++;


  int verify = 0;
  for(index i = 0; i != 3; ++i)
    for(index j = 0; j != 4; ++j)
      for(index k = 0; k != 2; ++k)
       {
         assert(A[i][j][k] == verify++);
        std::cout<<A[i][j][k] <<'\n' ;
        }


  return 0;
}
