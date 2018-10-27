#include <iostream>
#include <algorithm>  // for copy_if()
#include <cstring>
using namespace std;
 
void remove_extra_whitespaces(const char *input, char *output)
{
	//output.clear();  // unless you want to add at the end of existing sring...
	unique_copy (input, input+strlen(input)+1, output, [](char a,char b){ return isspace(a) && isspace(b);}); 
	cout << output<<endl; 
}
 
int main(int argc, char **argv)
{
    cout << "testing 2 ..\n";
 
    char input[0x255] = "asfa sas    f f dgdgd  dg   ggg";
    char output[0x255] = "NO_OUTPUT_YET";
    remove_extra_whitespaces(input,output);
 
    return 0;
}
