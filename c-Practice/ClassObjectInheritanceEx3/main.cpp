#include <iostream>
#include <stdio.h>
#include "Rectangle.h"
#include "Cost.h"

using namespace std;

int main()
{
	Rectangle rect;
	float cdi;
	rect.setBase(1);
	rect.setHeight(2);
  
	cout << "  area of rectangle" << rect.getAreaRect(12,12)<<endl;
	cout << rect.getArea() <<endl;
	
	Cost cst;
	cst.setCPA(2.89);
	cst.totalCost(rect);
	cst.getCD(10,12,5,15,&cdi);
	cout << cst.totalCost(rect)<<endl;
	cout << cdi<<endl;	
	return 0;
}
