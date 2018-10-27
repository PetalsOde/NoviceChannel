#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

int main() 
{

	ofstream ofs ("test.txt", ofstream::ate) ;
	ofs <<"lorem ipsum " ;
	ofs.close();
	
	
	return 0 ;
	
}



