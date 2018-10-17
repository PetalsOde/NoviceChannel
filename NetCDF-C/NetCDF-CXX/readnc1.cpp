#include <iostream>
#include <string>
#include <netcdf>
#include <cmath>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

// We are writing 4D data, a 2 x 6 x 12 lvl-lat-lon grid, with 2
// timesteps of data.
int NLVL;
int NLAT;
int NLON;
int NREC;

/*
These are used to construct some dimension data.
dimensions : longitude, latitude, pressure level, and time.
time is unlimited, 1460 currently .
*/

long int londimsize;
long int levdimsize;
long int latdimsize;
long double timdimsize;

// Return this code to the OS in case of failure.
//static const int NC_ERR = 2;

void mainair(const string &fname )
{
static const int NC_ERR = 2;
// These arrays will store the latitude and longitude values.

NcFile dataFile(fname.c_str(), NcFile::read);
// There are a number of inquiry functions in netCDF which can be
// used to learn about an unknown netCDF file.

cout<<"there are "<<dataFile.getVarCount()<<"=====variables"<<endl;
cout<<"there are "<<dataFile.getAttCount()<<"=====attributes"<<endl;
cout<<"there are "<<dataFile.getDimCount()<<"dimension"<<endl;
cout<<"there are "<<dataFile.getGroupCount()<<"Groups"<<endl;
cout<<"there are "<<dataFile.getTypeCount()<<"types"<<endl;


}
//*****************************************************************************************************

int main ()
{
	cout<<"reading is starting"<<endl;
	mainair( "air.2017.nc" );
	cout<<"reading is successful is done"<<endl;
	return 0;
}
