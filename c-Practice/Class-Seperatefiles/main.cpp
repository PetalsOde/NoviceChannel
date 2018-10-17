#include <iostream>
#include <string>
#include <math.h>

using namespace std;
#include "Books.h"
#include "Tria.h"
#include "Shape.h"

int main()
{ 
	Books book1;
	Books book2;
	book1.setBookId(1234);
	book2.setBookId(6789);
	cout<<book1.getBookId(67)<<endl;
	cout<<book2.getBookId(80)<<endl;
	
	Triangle triangle1;
	Triangle triangle2;
	triangle1.setBase(45);
	triangle1.setHeight(20);
	triangle2.setBase(24);
	triangle2.setHeight(25);
	
	
	cout<<triangle1.getTriangleperimeter()<<endl;	
	cout<<triangle2.getTriangleperimeter()<<endl;
	cout<<triangle1.getTrianglearea()<<endl;
	
	Rectangle rect1;
	rect1.setBase(12);
	rect1.setHeight(12);
	
	cout<<rect1.getRectanglearea()<<endl;
	return 0;
}
