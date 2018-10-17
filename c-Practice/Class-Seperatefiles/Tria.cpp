#include "Tria.h"

Triangle::Triangle()
{
}

void Triangle::setBase(int base_)
{
	base = base_+20;
}

void Triangle::setHeight(int height_)
{
	height = height_+20;
}

float Triangle :: getTrianglearea()
{
//	area = base * height * 0.5;
//	return area;
	return base * height * 0.5;
}

float Triangle :: getTriangleperimeter()
{	float side;
	float c = sqrt((pow((base/2),2) + (pow(height,2))));
	if ( c < (base + height))
	side = c;
	else 
	side = 0;
	return base + ( side * 2) ;
}




