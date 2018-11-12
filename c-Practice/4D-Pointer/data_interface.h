#pragma once
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
class Data_handle_read
{
	public :
		Data_handle_read();
		
		void data_4D_read(size_t &I_RECS ,size_t &I_LVLS, size_t &I_LATS,size_t &I_LONS, float *zpos, 
					float *ypos, float *xpos, double *tpos,	short *****var) ;
					
		void data_2D_read(size_t &I_LATS,size_t &I_LONS, 	float *ypos, float *xpos, short ***var) ;
};
