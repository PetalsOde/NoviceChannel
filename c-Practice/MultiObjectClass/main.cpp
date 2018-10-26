#include <iostream>
#include <stdio.h>
#include "Rectangle.h"


using namespace std;

int main()
{
	Rectangle rect;

	rect.setBase(1);
	rect.setHeight(2);
  
	cout << "  area of rectangle" << rect.getAreaRect(12,12)<<endl;
	cout << rect.getArea() <<endl;
	cout <<rect.getAreaCost(2.33) <<endl;
	return 0;
}
