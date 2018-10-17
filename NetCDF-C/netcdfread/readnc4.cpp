#include <iostream>
#include <string>
#include <netcdf>
#include <cmath>
#include <vector>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

template<class Type>
int Create3D_Array(Type ****pResult, int x, int y, int z)
{
    Type ***p = new Type **[x];
    for(int i = 0; i < x; i++)
    {
        p[i] = new Type *[y];
        for(int j = 0; j < y; j++)
            p[i][j] = new Type[z];
    }
    *pResult = p;
    return x * y * z;
}

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


//void netcdf_handle(const string &fname,  size_t &I_RECS, size_t &I_LATS, size_t &I_LONS, size_t &I_LVLS, float *ypos, float *xpos, float *zpos, double *tpos, short *****var )
void netcdf_handle(const string &fname, const string &vname,size_t &I_RECS ,size_t &I_LVLS, size_t &I_LATS, size_t &I_LONS, float *zpos, float *ypos, float *xpos, double *tpos  )
{
	int ncid, recid, latid, lonid, lvlid;
	int rec_varid, lat_varid , lon_varid, lvl_varid, var_varid;
	
	char recname[NC_MAX_NAME];
	nc_type xtype;
	
	
	nc_check( nc_open( fname.c_str(),  NC_NOWRITE | NC_NETCDF4, &ncid) );
	cout<<"file is opened"<<endl;
	
	nc_check( nc_inq_unlimdim ( ncid, &recid )); /* get ID of unlimited Dimension */
	nc_check( nc_inq_dimid ( ncid, "lat", &latid ) );
	nc_check( nc_inq_dimid ( ncid, "lon", &lonid ) );
	nc_check( nc_inq_dimid ( ncid, "level", &lvlid ) );
	
	nc_check( nc_inq_dim ( ncid, recid, recname, &I_RECS )) ; /* get unlimited dimension name and current length */
	nc_check( nc_inq_dimlen ( ncid, latid, &I_LATS ) ) ;
	nc_check( nc_inq_dimlen ( ncid, lonid, &I_LONS ) ) ;
	nc_check( nc_inq_dimlen ( ncid, lvlid, &I_LVLS ) ) ;
	
	nc_check( nc_inq_varid ( ncid, "time", &rec_varid ) ) ;
	nc_check( nc_inq_varid ( ncid, "lat", &lat_varid ) ) ;
	nc_check( nc_inq_varid ( ncid, "lon", &lon_varid ) ) ;
	nc_check( nc_inq_varid ( ncid, "level", &lvl_varid ) ) ;

	const size_t start_lon[] = {0};
    const size_t count_lon[] = {I_LONS};
	nc_check( nc_get_vara_float ( ncid,lon_varid, start_lon, count_lon, xpos ) );
	
	const size_t start_lat[] = {0};
    const size_t count_lat[] = {I_LATS};
	nc_check( nc_get_vara_float ( ncid,lat_varid, start_lat, count_lat, ypos ) );
	
	const size_t start_lvl[] = {0};
    const size_t count_lvl[] = {I_LVLS};
	nc_check( nc_get_vara_float ( ncid,lvl_varid, start_lvl, count_lvl, zpos ) );
	
	nc_check( nc_inq_vartype ( ncid, rec_varid, &xtype ) );
	if(xtype != NC_DOUBLE) 
	{
		cout << " The 'time' variable was not of type 'double'!\n"<< endl;
	}

	const size_t start_rec[] = {0};
    const size_t count_rec[] = {I_RECS};
	nc_check( nc_get_vara_double ( ncid,rec_varid, start_rec, count_rec, tpos ) );
	
	nc_check( nc_inq_varid ( ncid, vname.c_str(), &var_varid ) ) ;
	
	cout <<" I_RECS = " << I_RECS <<endl;
	cout <<" I_LATS = " << I_LATS << endl;
	cout <<" I_LONS = " << I_LONS << endl;
	cout <<" I_LVLS = " << I_LVLS << endl;
	cout <<" var_varid = " << var_varid << endl;
	
	
//	float ****p = *var;
	short temp[10*I_LVLS*I_LATS*I_LONS];
	const size_t start_1[] = {0,0,0,0};
    const size_t count_1[] = {1,I_LVLS,I_LATS,I_LONS};
	//static ptrdiff_t stride[] = {1,1,1,1};
	nc_check( nc_get_vara_short ( ncid,var_varid, start_1, count_1, temp ) );

	cout<<" temp[1] = "<< temp[1] <<endl;
	
	
	nc_check( nc_close(ncid) );
}

int main ()
{
	cout<<"reading is starting"<<endl;
	size_t I_RECS, I_LATS, I_LONS, I_LVLS;
	
	float* zpos = NULL;
	zpos = new float[I_LVLS];
	float* ypos = NULL;
	ypos = new float[I_LATS];
	float* xpos = NULL;
	xpos = new float[I_LONS];
	
//	double* tpos = NULL;
//	tpos = new double[I_RECS];

	double tpos[1500];
	
//	short ****air = NULL;
	
//	Create3D_Array(&air, 150, 75, 20);
	netcdf_handle( "air.2017.nc","air", I_RECS,I_LATS, I_LONS, I_LVLS, ypos, xpos, zpos, tpos);//, &air 
	cout <<" I_RECS = " << I_RECS <<endl;
	cout <<" I_LATS = " << I_LATS << endl;
	cout <<" I_LONS = " << I_LONS << endl;
	cout <<" I_LVLS = " << I_LVLS << endl;
	
	
	cout<<"ypos[0]   "<<ypos[0] << endl;
	cout<<"ypos[8]   "<<ypos[8] << endl;
	cout<<"reading is successful is done"<<endl;
	return 0;
}
