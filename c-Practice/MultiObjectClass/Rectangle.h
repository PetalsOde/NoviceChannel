#pragma once
#include <iostream>
#include <stdio.h>

class Rectangle
{
	public :
		int base;
		int height;
		void setBase(int base_);
		void setHeight(int height_);
		float getArea();
		int getAreaRect(int base_, int height_);
		float getAreaCost(float cpa);
		
};
