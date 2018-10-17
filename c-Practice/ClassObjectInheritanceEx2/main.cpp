#include <iostream>
#include <stdio.h>
#include <typeinfo>
#include "Rectangle.h"
#include "Cost.h"

using namespace std;

int main()
{
	Rectangle rect;
	rect.setBase(10);
	rect.setHeight(2);
	cout << "  area of rectangle" << rect.getAreaRect(1,12)<<endl;
	
	cout << rect.getArea() <<endl;
	
	Cost cst;
	cst.setCPA(2.89);
	
	cout << cst.totalCost(rect)<<endl;
	
	return 0;
	
}
