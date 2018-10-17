#include "Shape.h"

Rectangle::Rectangle()
{
}

void Rectangle::setBase(int base_)
{
	base = base_;
}

void Rectangle::setHeight(int height_)
{
	height = height_;
}

float Rectangle :: getRectanglearea()
{
	return base * height ;
}

float Rectangle :: getRectangleperimeter()
{	
	float c = sqrt((pow((base/2),2) + (pow(height,2))));
	return base + ( c * 2) ;
}




