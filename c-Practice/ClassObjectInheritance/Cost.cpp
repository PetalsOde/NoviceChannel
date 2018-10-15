#include "Cost.h"


void Cost::setCPA(float cost_per_area_)
{
	cost_per_area = cost_per_area_;
}

float Cost::totalCost(Rectangle rectt)
{
	area= rectt.getArea();
	tcost=(float)area * cost_per_area;
	return tcost;
}
void Cost::getCD(int base1,int height1,int base2,int height2,float *cdiff)
{
	Rectangle rect1;
	rect1.setBase(base1);
	rect1.setHeight(height1);
	Rectangle rect2;
	rect2.setBase(base2);
	rect2.setHeight(height2);
	float area1=rect1.getArea();
	float area2=rect2.getArea();
	*cdiff=(area1-area2)*cost_per_area;
}

float Cost::calcTotalCPA(float CPA_, int base_, int height_)
{
	Rectangle rect;
	
	area_rect = rect.getAreaRect(base_, height_);
	calctcost = area_rect * CPA_;
	return calctcost;
}






