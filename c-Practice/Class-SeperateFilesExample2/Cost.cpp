#include "Cost.h"
#include "Rectangle.h"

Rectangle rectt;

void Cost::setCPA(float cost_per_area_)
{
	cost_per_area = cost_per_area_;
}
void Cost::setDemand(int base_, int height_)
{
	area = rectt.getAreaRect(base_, height_);
	std :: cout<< area << "area "<<std ::endl;
}
void Cost::Printarea()
{
	std :: cout<< area << "area "<<std ::endl;
}

float Cost::getTotalCPA()
{
	return cost_per_area;
}




