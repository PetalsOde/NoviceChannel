#include "CostDiff.h"

void Costdiff::setCstDiff1(Cost cst1, Rectangle rect1)
{
	cstdiff1 = cst1.totalCost( rect1);
}
void Costdiff::setCstDiff2(Cost cst2, Rectangle rect2)
{
	cstdiff2 = cst2.totalCost( rect2);
}

float Costdiff::getCstDiff()
{
	costdiff = cstdiff2 - cstdiff1;
	return costdiff;
}

void Costdiff::setCalcCst1(float cpa1_, int base1_, int height1_)
{
	Cost cst1;
	calccst = cst1.calcTotalCPA(cpa1_, base1_, height1_);
}
/*
void Costdiff::setCalcCstDiff2(float cpa2_, int base2_, int height2_)
{
	Cost cst2;
	calccst2 = cst2.calcTotalCPA(cpa2_, base2_, height2_) ;
}
*/
float Costdiff::getCalcCst()
{
	return calccst;
}
