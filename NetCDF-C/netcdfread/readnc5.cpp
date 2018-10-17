#include <iostream>
#include <string>
#include <netcdf>
#include <cmath>
#include <vector>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

template<class Type>
int Create4D_Array(Type *****pResult, int a, int b, int c, int d)
{
    Type ****p = new Type ***[a];
    for(int i = 0; i < a; i++)
    {
        p[i] = new Type **[b];
        for(int j = 0; j < b; j++)
		{
			p[i][j] = new Type *[c];
			for(int k =0; k < c; k++)
			{
				p[i][j][k] = new Type [d];
			}
		}
		
    }
    *pResult = p;
    return  0;
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

void netcdf_handle(const string &fname, const string &vname,size_t &I_RECS ,size_t &I_LVLS, size_t &I_LATS, size_t &I_LONS, float *zpos, float *ypos, float *xpos, double *tpos, short *****var ) //,
//char *lat_unit, char *lon_unit, char *lvl_unit, char *rec_unit, char *var_unit )
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
	
	short var_data[10][I_LVLS][I_LATS][I_LONS];
	
	const size_t start_1[] = {0,0,0,0};
    const size_t count_1[] = {10,I_LVLS,I_LATS,I_LONS};
//	static ptrdiff_t stride[] = NULL;
	nc_check( nc_get_vars_short ( ncid, var_varid, start_1, count_1, NULL, &var_data[0][0][0][0] ) );

	cout<<"variable reading completed "<<endl;
	short ****p = *var;
	for (int i = 0; i < 10; i++ )
		for (int j = 0; j < I_LVLS; j++)
			for (int k = 0; k < I_LATS; k++)
				for (int l = 0; l < I_LONS; l++)
				{
					p[i][j][k][l] = var_data[i][j][k][l];
				};
	cout<<"now our variable got their values "<< endl;
	
	cout<<"var_data[2][2][2][2]   "<< var_data[2][2][2][2] <<endl;
	cout<<"var_data[2][16][70][140]   "<< var_data[2][16][70][140] << endl;
	
	
	size_t unit_latlen, unit_lonlen, unit_lvllen, unit_reclen, unit_varlen, add_offset_len, scale_factor_len  ;
	
	nc_check( nc_inq_attlen (ncid, lat_varid, "units", &unit_latlen ) );
	nc_check( nc_inq_attlen (ncid, lon_varid, "units", &unit_lonlen ) );
	nc_check( nc_inq_attlen (ncid, lvl_varid, "units", &unit_lvllen ) );
	nc_check( nc_inq_attlen (ncid, rec_varid, "units", &unit_reclen ) );
	
	nc_check( nc_inq_attlen (ncid, var_varid, "units", &unit_varlen ) );
	nc_check( nc_inq_attlen (ncid, var_varid, "add_offset", &add_offset_len ) );
	nc_check( nc_inq_attlen (ncid, var_varid, "scale_factor", &scale_factor_len ) );
	
//	cout<<"unit_varlen  "<< unit_varlen <<endl;
//	cout<<"add_offset_len  "<< add_offset_len <<endl;
//	cout<<"scale_factor_len  "<< scale_factor_len <<endl;
		
	char lat_unit[unit_latlen], lon_unit[unit_lonlen], lvl_unit[unit_lvllen], rec_unit[unit_reclen], var_unit[unit_varlen];
	float *var_add_offset, *var_scale_factor;
	cout<<" char array is generated "<< endl;
	cout<<"NC_MAX_NAME  "<< NC_MAX_NAME <<endl;
	var_add_offset = (float *) malloc(add_offset_len * sizeof(float));
	var_scale_factor = (float *) malloc(scale_factor_len * sizeof(float));
	
	nc_check( nc_get_att_text ( ncid, lat_varid, "units", lat_unit ) ) ;
	nc_check( nc_get_att_text ( ncid, lon_varid, "units", lon_unit ) ) ;
	nc_check( nc_get_att_text ( ncid, lvl_varid, "units", lvl_unit ) ) ;
	nc_check( nc_get_att_text ( ncid, rec_varid, "units", rec_unit ) ) ;
	cout<<"lat_unit =   "<< lat_unit <<endl;

	nc_check( nc_get_att_text ( ncid, var_varid, "units", var_unit ) ) ;
	nc_check( nc_get_att_float ( ncid, var_varid, "add_offset", var_add_offset ) ) ;
	nc_check( nc_get_att_float ( ncid, var_varid, "scale_factor", var_scale_factor ) ) ;
	
	cout<<" var_add_offset = "<< *var_add_offset <<endl;
	cout<<" var_scale_factor = "<< *var_scale_factor <<endl;
	cout<<" var_unit  = " << var_unit <<endl;
	
	float asd = float *var_add_offset ;
	cout<< " asd = "<< asd << endl;
	
	//cout<<"lat_unit =   "<< lat_unit <<endl;

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
	short ****air = NULL;
	
	double tpos[1500];
	
	Create4D_Array(&air, 20, 20, 75, 150 );
	
	netcdf_handle( "air.2017.nc","air", I_RECS, I_LVLS,I_LATS, I_LONS, zpos, ypos, xpos, tpos, &air );
	
	cout <<" I_RECS = " << I_RECS <<" I_LATS = " << I_LATS <<" I_LONS = " << I_LONS <<" I_LVLS = " << I_LVLS << endl;
	
/*	for (int lvl = 0; lvl< I_LVLS ; lvl++)
	{
		cout<<"lvl  "<< zpos[lvl] <<"  lvl  =  "<< lvl << endl;
	}
	for (int lat = 0; lat < I_LATS; lat++)
	{
		cout<<"lat  "<< ypos[lat]<< "   lat =  "<< lat <<endl;
	}
	for (int lon = 0; lon < I_LATS; lon++)
	{
		cout<<"lon  "<< xpos[lon]<< "   lon =  "<< lon <<endl;
	}
	for (int rec = 0; rec < I_RECS; rec++)
	{
		cout<< "time["<<rec<<"] = "<< tpos[rec]<<endl;
	}
	for (int i = 0; i < 2 ; i++ )
		for (int j = 0; j < 4; j++ ) // placing 10 instead of I_LVLS //
			for (int k = 0; k < 4; k++ )
				for (int l = 0; l < 4; l++ )
				{
					cout<<" air["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"] =  "<< air[i][j][k][l]<<endl;
				}
*/

	cout<<"ypos[0]   "<<ypos[0] <<"  xpos[0]   "<< xpos[0] <<" ypos[8]    "<<ypos[8] << endl;
	cout<<"zpos[0]   "<<zpos[0] <<"  zpos[1]   "<< zpos[1] <<" zpos[2]    "<<zpos[2]<< endl;
	cout<<"zpos[3]   "<<zpos[3] <<"  zpos[4]   "<< zpos[4] <<" zpos[5]    "<<zpos[5]<< endl;
	cout<<"zpos[6]   "<<zpos[6] <<"  zpos[7]   "<< zpos[7] <<" zpos[8]    "<<zpos[8]<< endl;
	cout<<"zpos[9]   "<<zpos[9] <<"  zpos[10]  "<< zpos[10]<<" zpos[11]   "<<zpos[11]<< endl;
	cout<<"zpos[12]   "<<zpos[12] <<"  zpos[13]  "<< zpos[13]<<" zpos[14]   "<<zpos[14]<< endl;
	cout<<"zpos[15]   "<<zpos[15] <<"  zpos[16]  "<< zpos[16]<< endl;
	cout<<"air[2][2][2][2]  "<< air[2][2][2][2] <<endl;
	cout<<"air[2][16][70][140]   "<< air[2][16][70][140] << endl;
	cout<<"reading is successful is done"<<endl;
	return 0;
}
