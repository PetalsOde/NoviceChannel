#include<iostream>
#include<string>
#include <cstdlib>
#include "data_mem.h"

using namespace std;		

int main ()
{

	short ****air = NULL;
	Data_mem dm;
	int x, y, z, w ;
	dm.data_storey(w, x, y, z, &air);
	
//	dm.Create4D_Array(&air, w, x, y, z );	
	
	for (int i = 0; i < w; i++ )
		for (int j = 0; j < x; j++)
			for (int k = 0; k < y; k++)
				for (int l = 0; l < z; l++)
				{
					std::cout<< "air = "<<air[i][j][k][l] <<'\n';
				}	

	std::cout<<w<<"    "<<x<<"    "<<y<<"     "<<z<<'\n' ;	
	std::cout<<"created" << '\n' ;
	return 0;
}
