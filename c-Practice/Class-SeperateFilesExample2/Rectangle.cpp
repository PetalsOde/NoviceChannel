#include "Rectangle.h"

void Rectangle ::setBase(int base_)
{
	base = base_;
}
void Rectangle::setHeight(int height_)
{
	height = height_;
}

int Rectangle::getArea()
{
	return base * height ;
}
int Rectangle::getAreaRect(int base_, int height_)
{
	return base * height ;
}
