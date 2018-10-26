#include "Rectangle.h"

void Rectangle ::setBase(int base_)
{
	base = base_;
}
void Rectangle::setHeight(int height_)
{
	height = height_;
}

float Rectangle::getArea()
{
	return (float)base * height ;
}
int Rectangle::getAreaRect(int base_, int height_)
{
	return base_ * height_ ;
}

float Rectangle::getAreaCost(float cpa)
{
	return (float)getArea() * cpa ;
}
