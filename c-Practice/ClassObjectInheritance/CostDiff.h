#pragma once 
#include <iostream>
#include <stdio.h>
#include "Rectangle.h"
#include "Cost.h"

class Costdiff: public Rectangle, 
				public Cost
{
	public :
		float costdiff;
		float cstdiff1;
		float cstdiff2;
		float calccst;
	//	float calccstdiff2;
		void setCstDiff1( Cost cst1, Rectangle rect1);
		void setCalcCst1(float cpa1_, int base1_, int height1_);
		void setCstDiff2( Cost cst2, Rectangle rect2);
	//	void setCalcCstDiff2(float cpa2_, int base2_, int height2_);
		float getCstDiff();
		float getCalcCst();


};
