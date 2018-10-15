#include<iostream>
#include<stdio.h>

using namespace std;
#include "LonGrid.h"

int main()
{
	int n_lons;
	float del_lon = 1.25;
	
	float* new_lon_pos = NULL;
	new_lon_pos = new float[n_lons];
	
	NewLonGrid Newlon;
	Newlon.new_lon_grid(new_lon_pos, n_lons, del_lon);

	for (int i =0 ; i< n_lons; i++)
	{
		cout << "lonpos["<<i<<"] = "<< new_lon_pos[i]<<endl;
	}
	cout<<"n_lons ="<<n_lons<<endl;



	return 0;
}