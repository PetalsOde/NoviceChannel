#pragma once 
#include <iostream>
#include <stdio.h>
#include <typeinfo>
#include "Rectangle.h"

class Cost: public Rectangle
{
	public :
		float tcost;
		float area;
		float cost_per_area;
		void setCPA(float cost_per_area_);
		float totalCost(Rectangle rect);
		void Printarea();
		float getTotalCPA();
		
};


