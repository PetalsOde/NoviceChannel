#pragma once 
#include <iostream>
#include <stdio.h>
#include "Rectangle.h"

class Cost: public Rectangle
{
	public :
		int area;
		float cost_per_area;
		void setDemand(int base_, int height_);
		void setCPA(float cost_per_area_);
		void Printarea();
		float getTotalCPA();
		
};


