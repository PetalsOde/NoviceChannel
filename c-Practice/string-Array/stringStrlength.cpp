// string::data
#include <iostream>
#include <string>
#include <cstring>

int main ()
{
  int length;

  std::string str = "Test string";
  char* cstr = "Test string";

  if ( str.length() == std::strlen(cstr) )
  {
    std::cout << "str and cstr have the same length.\n";

    if ( memcmp (cstr, str.data(), str.length() ) == 0 )
      std::cout << "str and cstr have the same content.\n";
  }
  return 0;
}
