#pragma once
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Triangle
{
	public:
		Triangle();
		int base;
		int height;
		void setBase(int base_);
		void setHeight(int height_);
		float getTrianglearea();
		float getTriangleperimeter();
		
};


