#include <iostream>
#include <string>
#include <netcdf>
#include <cmath>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

void nc_throw(const int return_value)
    {
        std::string error(nc_strerror(return_value));
        throw std::runtime_error(error);
    }

    void nc_check(const int return_value)
    {
        if (return_value != NC_NOERR)
            nc_throw(return_value);
    }


void netcdf_handle(const string &fname )
{
	int ncid;
	
	nc_check( nc_open( fname.c_str(),  NC_NOWRITE | NC_NETCDF4, &ncid) );
	cout<<"file is opened"<<endl;
	nc_check( nc_close(ncid) );
}

int main ()
{
	cout<<"reading is starting"<<endl;
	netcdf_handle( "air.2017.nc" );
	cout<<"reading is successful is done"<<endl;
	return 0;
}
