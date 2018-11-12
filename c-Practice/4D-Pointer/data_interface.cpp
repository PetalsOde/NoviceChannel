#include "data_interface.h"

Data_handle_read :: Data_handle_read()
{
}


void Data_handle_read::data_4D_read(size_t &I_RECS ,size_t &I_LVLS, size_t &I_LATS,size_t &I_LONS, float *zpos, 
					float *ypos, float *xpos, double *tpos,	short *****var)
{
	I_RECS = 5;
	I_LVLS = 5;
	I_LATS = 5;
	I_LONS = 5;
	float foo[5] = { 1000, 925, 850, 700, 600 };
	short ****p = *var;
	
	for (int t = 0; t < I_RECS; t++)
        {
        	tpos[t] = t * 24 * 60 ;
            std::cout<<"tpos["<<t<<"] = "<< tpos[t] << '\n' ;
        }
	for (int z = 0; z < I_LVLS; z++)
        {
        	zpos[z] = foo[z];
            std::cout<<"zpos["<<z<<"] = "<< zpos[z] << '\n' ;
        }
    for (int y = 0; y < I_LATS; y++)
        {
        	ypos[y] = 90 - (y * 2.5 ) ;
            std::cout<<"ypos["<<y<<"] = "<< ypos[y] << '\n' ;
        }
    for (int x = 0; x < I_LONS; x++)
        {
        	xpos[x] = 0 + (x * 2.5) ;
            std::cout<<"xpos["<<x<<"] = "<< xpos[x] << '\n' ;
        }
	
	for (int t = 0; t < I_RECS; t++)
	for (int z = 0; z < I_LVLS; z++)
	for (int y = 0; y < I_LATS; y++)
	for (int x = 0; x < I_LONS; x++)
	{
		std::cout<<" zpos["<<z<< "] = "<< zpos[z] << '\n' ;
		std::cout<<"working  t = " << t << "  z = "<< z<<"  y = "<< y <<"  x = " << x <<'\n' ;
		p[t][z][y][x] = 2 * tpos[t] + 4 * ypos[y] + (zpos[z] / 10) + (xpos[x] / 5 ) ;
	}
}

void Data_handle_read::data_2D_read(size_t &I_LATS,size_t &I_LONS, 	float *ypos, float *xpos, short ***var) 
{
	I_LATS = 5;
	I_LONS = 5;
	
	short **p = *var;
	for (int y = 0; y < I_LATS; y++)
	for (int x = 0; x < I_LONS; x++)
	{
		ypos[y] = 90 - (y * 2.5 ) ;
		xpos[x] = 0 + (x * 2.5) ;
		p[y][x] = 4 * ypos[y] + (xpos[x] / 5 ) ;
	}
}
