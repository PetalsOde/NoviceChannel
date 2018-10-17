#include "Cost.h"


void Cost::setCPA(float cost_per_area_)
{
	cost_per_area = cost_per_area_;
}

float Cost::totalCost(Rectangle rect)
{
	area= rect.getArea();
	tcost=(float)area * cost_per_area;
//	std::cout<<"function area "<<area << "  tcost = "<<tcost <<std ::endl;
//	std::cout <<typeid(area).name()<<std::endl;
//	std::cout <<typeid(tcost).name() <<std::endl;
	return tcost;
}


float Cost::getTotalCPA()
{
	return cost_per_area;
}




