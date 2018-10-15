#include "PassinPass.h"

void PassinPass::setAa( float a_)
{
	a = a_;
}
void PassinPass::setBb( float b_)
{
	b = b_;
}
void PassinPass::setCc( int c_)
{
	c = c_;
}
void PassinPass::setDd( int d_)
{
	d = d_;
}
void PassinPass::setEe( int e_)
{
	e = e_;
}
void PassinPass::setFf( int f_)
{
	f = f_;
}

float PassinPass::getCstDff()
{
	Costdiff cstdf1;
	cstdf1.setCalcCst1(a, c, e);
	calccst1 = cstdf1.getCalcCst();
	
	Costdiff cstdf2;
	cstdf2.setCalcCst1(b, d, f);
	calccst2 = cstdf2.getCalcCst();
	cstdff = calccst1 - calccst2;	
	return cstdff;
}
void PassinPass::getCalcCst(float aa, int bb, int cc, float *dd)
{
	Costdiff cstdff;
	cstdff.setCalcCst1(aa, bb, cc);
	*dd = cstdff.getCalcCst();
	cout<<"dd = "<< *dd<<endl;
}



