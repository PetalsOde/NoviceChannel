#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

int main() 
{
	std :: string lineread ;
	std::ifstream ofs ("test.txt",std::ofstream::in) ;
	getline(ofs, lineread) ;
	std :: cout<<lineread ;
	ofs.close();
	
	return 0 ;
	
}
