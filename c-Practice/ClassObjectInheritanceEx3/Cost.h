#pragma once 
#include <iostream>
#include <stdio.h>
#include "Rectangle.h"

class Cost: public Rectangle
{
	public :
		float tcost;
		float area;
		float cost_per_area;
		void setCPA(float cost_per_area_);
		float totalCost(Rectangle rectt);
		void Printarea();
		float getTotalCPA();
		void getCD(int base1,int height1,int base2,int height2,float *cdiff);
};


