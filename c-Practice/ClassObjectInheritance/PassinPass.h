#pragma once
#include <iostream>
#include <stdio.h>
#include "Rectangle.h"
#include "Cost.h"
#include "CostDiff.h"
using namespace std;

class PassinPass: public Rectangle,
				   public Cost,
				   public Costdiff
{
	public :
		float a;
		float b;
		int c;
		int d;
		int e;
		int f;
		float cstdff;
		float calccst1;
		float calccst2;
		void setAa( float a_);
		void setBb( float b_);
		void setCc( int c_);
		void setDd( int d_);
		void setEe( int e_);
		void setFf( int f_);
		float getCstDff();
		void getCalcCst(float aa, int bb, int cc, float *dd);
		
};



