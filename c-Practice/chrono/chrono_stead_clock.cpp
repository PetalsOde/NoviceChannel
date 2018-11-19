#include<iostream>
#include <chrono>
#include <string>

int main()
{
//      RANDOM DATA IS CREATING IN MAIN PROGRAM
        auto start = std::chrono::steady_clock::now();

        auto end = std::chrono::steady_clock::now();

        std::cout << "Elapsed time in nanoseconds : "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
                << " ns" << std::endl;



        float asdf = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() ;
        std::cout<<"float value asdf = "<< asdf << std::endl;

        std::cout << "Elapsed time in microseconds : "
                << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                << " µs" << std::endl;

        std::cout << "Elapsed time in milliseconds : "
                << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                << " ms" << std::endl;

        std::cout << "Elapsed time in seconds : "
                << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
                << " sec"<<'\n';

        std::cout<<std::to_string(std::chrono::duration_cast<std::chrono::seconds>(end - start).count()) <<'\n' ;

                return 0;
}
