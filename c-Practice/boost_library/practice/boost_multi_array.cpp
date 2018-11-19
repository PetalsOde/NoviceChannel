#include "boost/multi_array.hpp"
#include <cassert>

int main ()
{
	int  I_LATS, I_LONS, I_LVLS;
  I_LATS = 5, I_LONS = 5 , I_LVLS = 5 ;	

  // Create a 3D array that is 3 x 4 x 2
  typedef boost::multi_array<double, 3> array_type1;
  typedef boost::multi_array<double, 3> array_type2;
  typedef boost::multi_array<double, 3> array_type3;
  typedef boost::multi_array<double, 3> array_type4;
  typedef boost::multi_array<double, 3> array_type5;
  typedef boost::multi_array<double, 3> array_type6;
  typedef array_type1::index index;
  typedef array_type2::index index;
  typedef array_type3::index index;
  typedef array_type4::index index;
  typedef array_type5::index index;
  typedef array_type6::index index;
  array_type1 A1(boost::extents[I_LVLS][I_LATS][I_LONS]);
  array_type2 A2(boost::extents[I_LVLS][I_LATS][I_LONS]);
  array_type3 A3(boost::extents[I_LVLS][I_LATS][I_LONS]);
  array_type4 A4(boost::extents[I_LVLS][I_LATS][I_LONS]);
  array_type5 A5(boost::extents[I_LVLS][I_LATS][I_LONS]);
  array_type6 A6(boost::extents[I_LVLS][I_LATS][I_LONS]); 


  // Assign values to the elements
  int values1 = 0;
  int values2 = 1;
  int values3 = 2;
  int values4 = 3;
  int values5 = 4;
  int values6 = 5;
  for(index i = 0; i != 3; ++i) 
    for(index j = 0; j != 4; ++j)
      for(index k = 0; k != 2; ++k)
      {
      	A1[i][j][k] = values1++;
      	A2[i][j][k] = values2++;
      	A3[i][j][k] = values3++;
      	A4[i][j][k] = values4++;
      	A5[i][j][k] = values5++;
      	A6[i][j][k] = values6++;  	
      	
	  }
        

  // Verify values
  int verify = 0;
  for(index i = 0; i != 3; ++i) 
    for(index j = 0; j != 4; ++j)
      for(index k = 0; k != 2; ++k)
      {
      	std::cout<<"a1["<<i<<"]["<<j<<"]["<<k<<"] =  "<<A1[i][j][k] << '\n' ;
      	std::cout<<"a2["<<i<<"]["<<j<<"]["<<k<<"] =  "<<A2[i][j][k] << '\n' ;
      	std::cout<<"a3["<<i<<"]["<<j<<"]["<<k<<"] =  "<<A3[i][j][k] << '\n' ;
      	std::cout<<"a4["<<i<<"]["<<j<<"]["<<k<<"] =  "<<A4[i][j][k] << '\n' ;
      	std::cout<<"a5["<<i<<"]["<<j<<"]["<<k<<"] =  "<<A5[i][j][k] << '\n' ;
      	std::cout<<"a6["<<i<<"]["<<j<<"]["<<k<<"] =  "<<A6[i][j][k] << '\n' ;
	  }

  return 0;
}
