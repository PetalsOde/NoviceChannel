#include <iostream>
#include <string>
#include <netcdf>
#include <cmath>
#include <vector>
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


void netcdf_handle(const string &fname, size_t &I_RECS, size_t &I_LATS, size_t &I_LONS, size_t &I_LVLS )
{
	int ncid, recid, latid, lonid, lvlid;
	//size_t recs;
	char recname[NC_MAX_NAME];
	
	nc_check( nc_open( fname.c_str(),  NC_NOWRITE | NC_NETCDF4, &ncid) );
	cout<<"file is opened"<<endl;
	
	nc_check( nc_inq_unlimdim( ncid, &recid )); /* get ID od unlimited Dimension */
	nc_check( nc_inq_dimid ( ncid, "lat", &latid ) );
	nc_check( nc_inq_dimid ( ncid, "lon", &lonid ) );
	nc_check( nc_inq_dimid ( ncid, "level", &lvlid ) );
	
	nc_check( nc_inq_dim ( ncid, recid, recname, &I_RECS )) ; /* get unlimited dimension name and current length */
	nc_check( nc_inq_dimlen ( ncid, latid, &I_LATS ) ) ;
	nc_check( nc_inq_dimlen ( ncid, lonid, &I_LONS ) ) ;
	nc_check( nc_inq_dimlen ( ncid, lvlid, &I_LVLS ) ) ;
	
	cout<<"&I_LATS = "<<I_LATS<< endl;
	cout<<" &I_LONS = " << I_LONS << endl;
	cout<< " &I_LVLS = "<< I_LVLS << endl;	
	cout <<" recname = "<< recname << "   I_RECS = "<<I_RECS << " &I_RECS = " << &I_RECS <<endl;
	
	nc_check( nc_close(ncid) );
}

int main ()
{
	cout<<"reading is starting"<<endl;
	size_t I_RECS, I_LATS, I_LONS, I_LVLS;
	netcdf_handle( "air.2017.nc", I_RECS,I_LATS, I_LONS, I_LVLS);
	cout << "   I_RECS = "<< I_RECS <<endl;
	cout<<"&I_LATS = "<< I_LATS<< endl;
	cout<<" &I_LONS = " << I_LONS << endl;
	cout<< " &I_LVLS = "<< I_LVLS << endl;	
	cout<<"reading is successful is done"<<endl;
	return 0;
}
