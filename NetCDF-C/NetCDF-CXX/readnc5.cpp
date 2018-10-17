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
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); return 2;}
void handle_error(int status) {
if (status != NC_NOERR) {
	fprintf(stderr, "%s\n", nc_strerror(status));
		exit(-1);
		}
	}

// Return this code to the OS in case of failure.
//static const int NC_ERR = 2;

void mainair(const string &fname, const string &vname, const string &units, int& NLAT, int& NLON, int& NLVL, int& NREC, float *zpos, float *ypos, float *xpos, string latunits , string lonunits, 
string levunits, string timunits, string airunits)
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

levVar = dataFile.getVar("level");
if(levVar.isNull()) return ;

timVar = dataFile.getVar("time");
if(timVar.isNull()) return ;

lonVar.getVar(lons);
latVar.getVar(lats);
levVar.getVar(levs);
timVar.getVar(tims);


for (int lvl = 0; lvl < NLVL; lvl++)
{
	zpos[lvl] = levs[lvl];
//	cout<<"lvl  "<< zpos[lvl]<<endl;
}
for (int lat = 0; lat < NLAT; lat++)
{
	ypos[lat] = lats[lat];
//	cout<<"lat  "<<ypos[lat]<<endl;

}
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
/*
//int i=0;  //used in the data generation loop
for (int lvl = 0; lvl < NLVL; lvl++)
for (int lat = 0; lat < NLAT; lat++)
for (int lon = 0; lon < NLON; lon++)
 {
  air[lon][lat][lvl] = 0 ; //var[lvl][lat][lon] ;
//  cout<< air[lon][lat][lvl] << endl;
 }
*/
 
 
 NcVarAtt att;
//string lonunits,levunits,timunits,airunits;

att = latVar.getAtt(units.c_str());
if(att.isNull()) return ;
att.getValues(latunits);
cout<<"getvalue returned, latunits =  "<< latunits << endl;
cout<<"getvalue returned, latunits =  "<< &latunits << endl;


att = lonVar.getAtt(units.c_str());
if(att.isNull()) return ;
att.getValues(lonunits);
cout<<"getvalue returned, latunits =  "<<lonunits<< endl;

att = levVar.getAtt(units.c_str());
if(att.isNull()) return ;
att.getValues(levunits);
cout<<"getvalues returned, lonunits =  "<< levunits<< endl;

att = timVar.getAtt(units.c_str());
if(att.isNull()) return ;
att.getValues(timunits);
cout<<"getValues returned, levunits = "<<timunits<< endl;

att =dataVar.getAtt(units.c_str());
if(att.isNull()) return ;
att.getValues(airunits);
cout<<"getvalues returned, airunits =  "<< airunits << endl;
 /*
int lat_varid, ncid, status ;
 
char latunits_new[100];
if ((status  = nc_inq_varid(ncid, "latitude", &lat_varid)))
if (status != NC_NOERR) handle_error(status);
 
if ((status  = nc_get_att_text(ncid, lat_varid, units.c_str(), latunits_new)))
if (status != NC_NOERR) handle_error(status);
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

	string latunits, lonunits,levunits,timunits,airunits;
		
	mainair( "air.2017.nc", "air" , "units",  NLAT, NLON, NLVL, NREC, zpos, ypos, xpos, latunits, lonunits,levunits,timunits,airunits);
	cout<<"reading is successful is done"<<endl;
	cout << "longitude dimension is =="<< NLON <<endl;
	cout << "latitude dimension is =="<< NLAT <<endl;
	cout << "level dimension is =="<< NLVL <<endl;
	cout << "TIME dimension is =="<< NREC <<endl;
	
	cout << "from main section, latitude units will print here == "<< &latunits << endl;
		
	
	return 0;
}
