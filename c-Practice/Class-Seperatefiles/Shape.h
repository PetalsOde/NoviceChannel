#pragma once
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Rectangle
{
	public:
		Rectangle();
		int base;
		int height;
		void setBase(int base_);
		void setHeight(int height_);
		float getRectanglearea();
		float getRectangleperimeter();
		
};


