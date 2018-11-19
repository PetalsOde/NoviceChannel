#include <iostream>
#include "current_time_.h"

using namespace std;

int main(int argc, char** argv) {
    CurrentTime current_time;

    int start1 = current_time.milliseconds();
    int start2 = current_time.microseconds();
    int start3 = current_time.nanoseconds();
    int point1, point2, point3 ;
    current_time.timings(point1, point2, point3);

    for (int i = 0; i < 100000000; ++i) {

    }
        int n_point1, n_point2, n_point3;
    current_time.timings(n_point1, n_point2, n_point3);



    int end1 = current_time.milliseconds();
    int end2 = current_time.microseconds();
    int end3 = current_time.nanoseconds();


    cout << "Milliseconds: "   << (end1 - start1)
         << ", microseconds: " << (end2 - start2)
         << ", nanoseconds: "  << (end3 - start3)
         << ".\n";

    cout << "Milliseconds: "   << (n_point3 - point3)
         << ", microseconds: " << (n_point2 - point2)
         << ", nanoseconds: "  << (n_point1 - point1)
         << ".\n";

    return 0;
}
