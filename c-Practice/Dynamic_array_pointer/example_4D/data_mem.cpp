#include "data_mem.h"

void Data_mem::data_storey(int &w, int &x, int &y, int &z, short *****var)
{
	std::cout<<"Enter the values for w, x, y, z : ";
	std::cin>>w ;
	std::cin>>x ;
	std::cin>>y ;
	std::cin>>z ;
	
	short ****p = NULL;
	Create4D_Array(&p, w, x, y, z );
	
	for (int i = 0; i < w; i++ )
		for (int j = 0; j < x; j++)
			for (int k = 0; k < y; k++)
				for (int l = 0; l < z; l++)
				{
					p[i][j][k][l] = i + j + k + l ;
					std::cout<< p[i][j][k][l] <<'\n';
				};	
				
	*var = p ;
}
