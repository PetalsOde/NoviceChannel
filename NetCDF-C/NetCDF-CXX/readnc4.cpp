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


// Return this code to the OS in case of failure.
//static const int NC_ERR = 2;

void mainair(const string &fname, const string &vname, int& NLAT, int& NLON, int& NLVL, int& NREC, float *zpos, float *ypos, float *xpos, float ****air)
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


// These arrays will hold the data we will read in. We will only
// need enough space to hold one timestep of data; one record.
short var[NLVL][NLAT][NLON] ;


// Get the main variables and read data one time step at a time
NcVar dataVar;
dataVar = dataFile.getVar(vname.c_str());
if(dataVar.isNull()) return ;

vector <size_t> startp,countp;
startp.push_back(0);
startp.push_back(0);
startp.push_back(0);
startp.push_back(0);
countp.push_back(1);
countp.push_back(NLVL);
countp.push_back(NLAT);
countp.push_back(NLON);

for (size_t rec = 0; rec < NREC; rec++)
{
// Read the data one record at a time.

startp[0]=rec;
dataVar.getVar(startp,countp,var);
}

//int i=0;  //used in the data generation loop

float ***p = *air;
for (int lon = 0; lon < NLON; lon++)
	{
	//	cout<<"lon cycle is started     "<< lon <<endl;
		for (int lat = 0; lat < NLAT; lat++)
			{
			//	cout<<"lat cycle is started     "<<lat << endl;
				for (int lvl = 0; lvl < NLVL; lvl++)
					{
					//	cout<< "lvl cycle is started    " << lvl << endl;
						p[lon][lat][lvl] = var[lvl][lat][lon] ;
						  
						
					//	std :: cout << "all is well   "<<"i ="<<lon << "j ="<<lat <<"k ="<<lvl << "     "<< " p = "<< p[lon][lat][lvl] << std :: endl;
					}
			}
	};
cout << "***happening airvar reading netcdf!" << endl;
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
	
	float ***air = NULL;
/*	
	air = new float **[NLON];
	for (int i = 0; i < NLON; i++)
	{
		air[i] = new float *[NLAT];
		for (int j = 0; j <NLAT; j++ )
			air[i][j] = new float [NLVL];
	}
*/
	Create3D_Array(&air, 150, 75, 20);

	cout<<"xpos[0]   "<<xpos[0]<<endl;
	cout<<"ypos[0]   "<<ypos[0] << endl;
	cout<< "zpos[0]    "<< zpos[0] << endl;
		
	mainair( "air.2017.nc", "air" , NLAT, NLON, NLVL, NREC, zpos, ypos, xpos, &air);
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
	
	for (int lon = 0; lon < NLON; lon++ )
		for ( int lat = 0; lat < NLAT; lat++)
			for (int lvl = 0; lvl < NLVL; lvl++)
				{
					cout<<"air = "<< air[lon][lat][lvl]<<endl;
					//cout<<"lvl  "<< zpos[lvl]<<"   lvlid  "<<lvl <<"  NLVL  "<< NLVL <<endl;
	}	
	
	
	return 0;
}
