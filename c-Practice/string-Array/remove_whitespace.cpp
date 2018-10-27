#include <iostream>
#include <string>     // forget about char[] and char*: use string instead !  
#include <algorithm>  // for copy_if()
#include <iterator>   // for the back_inserter
using namespace std;
 
void remove_extra_whitespaces(const string &input, string &output)
{
	output.clear();  // unless you want to add at the end of existing sring...
	unique_copy (input.begin(), input.end(), back_insert_iterator<string>(output), [](char a,char b){ return isspace(a) && isspace(b);});  
	cout << output<<endl; 
}
 
int main(int argc, char **argv)
{
    cout << "testing 2 ..\n";
 
    string input = "asfa sas    f f dgdgd  dg   ggg";
    string output = "NO_OUTPUT_YET";
    remove_extra_whitespaces(input,output);
 
    return 0;
}

