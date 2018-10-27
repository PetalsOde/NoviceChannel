#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>



int main() 
{
	
	std::ofstream ofs ("test.txt",std::ofstream::app) ;
	ofs <<"lorem ipsum " <<std::endl;
	
	
	ofs.close();
	return 0 ;
	
}



