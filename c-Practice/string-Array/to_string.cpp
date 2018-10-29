#include <iostream>
#include <string>
 
int main() 
{
    double f = 23.43;
    double f2 = 1e-9;
    double f3 = 1e40;
    double f4 = 1e-40;
    double f5 = 123456789;
    std::string f_str = std::to_string(f);
    std::string f_str2 = std::to_string(f2); // Note: returns "0.000000"
    std::string f_str3 = std::to_string(f3); // Note: Does not return "1e+40".
    std::string f_str4 = std::to_string(f4); // Note: returns "0.000000"
    std::string f_str5 = std::to_string(f5);
    std::cout << "std::cout: " << f << '\n'
              << "to_string: " << f_str  << "\n\n"
              << "std::cout: " << f2 << '\n'
              << "to_string: " << f_str2 << "\n\n"
              << "std::cout: " << f3 << '\n'
              << "to_string: " << f_str3 << "\n\n"
              << "std::cout: " << f4 << '\n'
              << "to_string: " << f_str4 << "\n\n"
              << "std::cout: " << f5 << '\n'
              << "to_string: " << f_str5 << '\n';
}
