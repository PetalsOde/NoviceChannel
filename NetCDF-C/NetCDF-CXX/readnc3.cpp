#include <iostream>
#include <string>
#include <netcdf>
#include <cmath>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

// We are writing 4D data, a 2 x 6 x 12 lvl-lat-lon grid, with 2
// timesteps of data.

/*
These are used to construct some dimension data.
dimensions : longitude, latitude, pressure level, and time.
time is unlimited, 1460 currently .
*/



// Return this code to the OS in case of failure.
//static const int NC_ERR = 2;

void mainair(const string &fname, int& NLAT, int& NLON, int& NLVL, int& NREC, float *zpos, float *ypos, float *xpos)
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


// Define the dimensions. NetCDF will hand back an ncDim object foreach.
NcDim timdim, latdim, londim, levdim;

long int londimsize;
long int levdimsize;
long int latdimsize;
long double timdimsize;
// These arrays will store the latitude and longitude values.
timdim= dataFile.getDim("time");
timdimsize =  timdim.getSize();
NREC=timdimsize;

// These arrays will store the latitude and longitude values.
levdim= dataFile.getDim("level");
levdimsize =  levdim.getSize();
NLVL=levdimsize;

londim= dataFile.getDim("lon");
londimsize =  londim.getSize();
NLON=londimsize;

latdim = dataFile.getDim("lat");
latdimsize = latdim.getSize();
NLAT=latdimsize;

cout << "***happening reading netcdf!" << endl;

float lats[NLAT], lons[NLON],levs[NLVL];
double tims[NREC];

try
   {
// Get the latitude and longitude variables and read data.
NcVar latVar, lonVar, levVar, timVar;

latVar = dataFile.getVar("lat");
if(latVar.isNull()) return ;
cout << "***happening latvar reading netcdf!" << endl;

lonVar = dataFile.getVar("lon");
if(lonVar.isNull()) return ;
cout << "***happening lonvar reading netcdf!" << endl;

levVar = dataFile.getVar("level");
if(levVar.isNull()) return ;
cout << "***happening levvar reading netcdf!" << endl;

timVar = dataFile.getVar("time");
if(timVar.isNull()) return ;
cout << "***happening timvar reading netcdf!" << endl;

lonVar.getVar(lons);
latVar.getVar(lats);
levVar.getVar(levs);
timVar.getVar(tims);
cout << "***happening lons, lats, levs, tims reading netcdf!" << endl;


for (int lvl = 0; lvl < NLVL; lvl++)
{
	zpos[lvl] = levs[lvl];
//	cout<<"lvl  "<< zpos[lvl]<<endl;
}
cout<< " ****** **** ************ zpos[NLAT]   "<< zpos[NLVL-1] << endl;
for (int lat = 0; lat < NLAT; lat++)
{
	ypos[lat] = lats[lat];
//	cout<<"lat  "<<ypos[lat]<<endl;

}
cout<< " ****** **** ************ ypos[NLAT]  "<< ypos[NLAT-1] << endl;
for (int lon = 0; lon < NLON; lon++)
{
	xpos[lon] = lons[lon];
//	cout<<"lon  "<<xpos[lon]<<endl;
}
/*
for (size_t rec = 0; rec < NREC; rec++)
{
	tpos[rec] = tims[rec];
}
*/

cout << "*** SUCCESS reading netcdf!" << endl;
return ;
}

catch(NcException& e)
{
e.what();
cout<<"FAILURE**************************"<<endl;
return ;//NC_ERR;
}
}
//*****************************************************************************************************

int main ()
{
	cout<<"reading is starting"<<endl;

	int NLAT = 0, NLON = 0 ,  NLVL = 0, NREC = 0;
	
	float* zpos = NULL;
	zpos = new float[NLVL];
	float* ypos = NULL;
	ypos = new float[NLAT];
	float* xpos = NULL;
	xpos = new float[NLON];

	cout<<"xpos[0]   "<<xpos[0]<<endl;
	cout<<"ypos[0]   "<<ypos[0] << endl;
	cout<< "zpos[0]    "<< zpos[0] << endl;
		
	mainair( "air.2017.nc", NLAT, NLON, NLVL, NREC, zpos, ypos, xpos);
	cout<<"reading is successful is done"<<endl;
	cout << "longitude dimension is =="<< NLON <<endl;
	cout << "latitude dimension is =="<< NLAT <<endl;
	cout << "level dimension is =="<< NLVL <<endl;
	cout << "TIME dimension is =="<< NREC <<endl;
	
	
		
	cout<<"ypos[0]   "<<ypos[0] << endl;
	cout<<"xpos[0]   "<<xpos[0]<<endl;
	
	
	cout<<"xpos[0]   "<<xpos[0]<<endl;
	cout<<"ypos[0]   "<<ypos[0] << endl;
	cout<<"ypos[8]   "<<ypos[8] << endl;
	cout<<"zpos[9]   "<<zpos[9] << endl;
	cout<<"zpos[12]   "<<zpos[12] << endl;
	cout<<"zpos[15]   "<<zpos[15] << endl;
	cout<<"zpos[10]   "<<zpos[10] << endl;
	cout<<"zpos[16]   "<<zpos[16] << endl;
	
	for (int lvl = 0; lvl < NLVL; lvl++ )
	{
		cout<<"lvl  "<< zpos[lvl]<<"   lvlid  "<<lvl <<"  NLVL  "<< NLVL <<endl;
	}	
	
	
	return 0;
}
