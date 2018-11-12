#include "printdata.h"

void Data_Print::print_4D_data(size_t &I_RECS ,size_t &I_LVLS, size_t &I_LATS,size_t &I_LONS, float *zpos, 
					float *ypos, float *xpos, double *tpos,	short *****var)
{
	short ****p = *var;
	
	for (int t = 0; t < I_RECS; t++)
        {
            std::cout<<"tpos["<<t<<"] = "<< tpos[t] << '\n' ;
        }
	for (int z = 0; z < I_LVLS; z++)
        {
            std::cout<<"zpos["<<z<<"] = "<< zpos[z] << '\n' ;
        }
    for (int y = 0; y < I_LATS; y++)
        {
            std::cout<<"ypos["<<y<<"] = "<< ypos[y] << '\n' ;
        }
    for (int x = 0; x < I_LONS; x++)
        {
            std::cout<<"xpos["<<x<<"] = "<< xpos[x] << '\n' ;
        }
	
	for (int t = 0; t < I_RECS; t++)
	for (int z = 0; z < I_LVLS; z++)
	for (int y = 0; y < I_LATS; y++)
	for (int x = 0; x < I_LONS; x++)
	{
		std::cout<<"p["<<t<<"]["<<z<<"]["<<y<<"]["<<x<<"] = " <<p[t][z][y][x] <<'\n' ;
		
	}
}

void Data_Print::print_2D_data(size_t &I_LATS,size_t &I_LONS, float *ypos, float *xpos, short ***var)
{
	short **p = *var;
	for (int y = 0; y < I_LATS; y++)
        {
            std::cout<<"ypos["<<y<<"] = "<< ypos[y] << '\n' ;
        }
    for (int x = 0; x < I_LONS; x++)
        {
            std::cout<<"xpos["<<x<<"] = "<< xpos[x] << '\n' ;
        }
    
	for (int y = 0; y < I_LATS; y++)
	for (int x = 0; x < I_LONS; x++)
	{
		std::cout<<"p["<<y<<"]["<<x<<"] = " <<p[y][x] <<'\n' ;		
	}
	
}
