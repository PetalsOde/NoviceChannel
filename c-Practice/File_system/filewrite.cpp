#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

int main() 
{
	ofstream ofs ("test.txt", ofstream::out) ;
	ofs <<"lorem ipsum " <<std::endl;
	
	ofs.close();
	return 0 ;
	
}



