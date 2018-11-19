#include <iostream>
#include <array>

using namespace std;

void printArray(const std::array<int, m> &n, int m)
{
    std::cout << "length: " << n.size() << endl;

    for (int j = 0; j < n.size(); j++ )
    {
        cout << "n[" << j << "] = " << n[j] << endl;
    }

}

int main()
{

    int m = 5;
    array<int, m> n = {1,2,3,4,5};

    printArray(n);

    return 0;
}
