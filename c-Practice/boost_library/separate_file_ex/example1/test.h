#pragma once
#include "boost/multi_array.hpp"

class Assign_Data
{
        public :
                void assign_data(boost::multi_array<double, 4> &arr, int &nx, int &ny, int &nz, int &nt );
};
