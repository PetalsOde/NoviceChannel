#pragma once
#include <iostream>
#include <string>
#include <cmath> 

class Data_Print
{
	public:
		void print_4D_data(size_t &I_RECS ,size_t &I_LVLS, size_t &I_LATS,size_t &I_LONS, float *zpos, 
					float *ypos, float *xpos, double *tpos,	short *****var) ;
					
		void print_2D_data(size_t &I_LATS,size_t &I_LONS, float *ypos, float *xpos, short ***var) ;
};
