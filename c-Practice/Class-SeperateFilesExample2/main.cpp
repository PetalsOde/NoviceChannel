#include <iostream>
#include <stdio.h>
#include "Rectangle.h"
#include "Cost.h"

using namespace std;

int main()
{
	Rectangle rect;
	rect.setBase(12);
	rect.setHeight(12);
	cout << "  area of rectangle" << rect.getAreaRect(12,12)<<endl;
	
	cout << rect.getArea() <<endl;
	
	Cost cst;
	cst.setCPA(2.89);
	cst.setDemand(12, 12);
	cst.Printarea();
	
	cout << cst.getTotalCPA()<<endl;
	
	
	return 0;
	
}
