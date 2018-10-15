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
		float calctcost;
		float area_rect;
		void setCPA(float cost_per_area_);
		float totalCost(Rectangle rectt);
		void Printarea();
		float getTotalCPA();
		float calcTotalCPA( float CPA_, int base_, int height_);
		void getCD(int base1,int height1,int base2,int height2,float *cdiff);
};


