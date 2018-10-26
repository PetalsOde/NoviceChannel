
// CPP program to illustrate substr() 
#include <string.h> 
#include <iostream> 
using namespace std; 
  
int main() 
{ 
    // Take any string 
    string s = "dog:cat   cat&dog"; 
  

	// Copy substring before pos 
    string sub = s.substr(13 ,0001); 
    cout <<"sub  value is  = " << sub << endl;
    
    // Find position of ':' using find() 
    int pos = s.find("&"); 
  
    // Copy substring after pos 
    sub = s.substr(pos ,3); 
    cout <<"pos  value is  = " << pos << endl;
    
  
    // prints the result 
    cout << "String is: " << sub; 
  
    return 0; 
} 
