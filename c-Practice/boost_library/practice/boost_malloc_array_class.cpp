#include <iostream>
#include <chrono>
#include <boost/multi_array.hpp>

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
class Assign_Data_malloc
{
	public:		
		void assign_data(double *****arr, int &nx, int &ny, int &nz, int &nt )
		{
			double ****p = *arr;
			int values1 = 0;
			for (int i = 0 ; i < nx ; i++ )
			for (int j = 0 ; j < ny ; j++ )
			for (int k = 0 ; k < nz ; k++ )
			for (int l = 0 ; l < nt ; l++ )			
			{
				p[i][j][k][l] = values1++;
				
			//	std::cout<<"arr["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"] =  "<<p[i][j][k][l] << '\n' ;
			}
			*arr = p;
		}; 
};

class Assign_Data_boost
{
	public:		
		void assign_data(boost::multi_array<double, 4> &arr, int &nx, int &ny, int &nz, int &nt )
		{
			int values1 = 0;
			for (int i = 0 ; i < nx ; i++ )
			for (int j = 0 ; j < ny ; j++ )
			for (int k = 0 ; k < nz ; k++ )
			for (int l = 0 ; l < nt ; l++ )			
			{
				arr[i][j][k][l] = values1++;
				
			//	std::cout<<"arr["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"] =  "<<arr[i][j][k][l] << '\n' ;
			}
		}; 
};

int main()
{
	int  I_LATS, I_LONS, I_LVLS, I_RECS;
	I_LATS = 73, I_LONS = 144 , I_LVLS = 17, I_RECS = 7300 ;
	
	auto start_malloc = std::chrono::steady_clock::now();	
	
	double ****A_m1 = NULL;
	double ****A_m2 = NULL;
	double ****A_m3 = NULL;
	double ****A_m4 = NULL;
	double ****A_m5 = NULL;
	double ****A_m6 = NULL;
  	
	Create4D_Array(&A_m1, I_RECS, I_LVLS, I_LATS, I_LONS);	
	Create4D_Array(&A_m2, I_RECS, I_LVLS, I_LATS, I_LONS);
	Create4D_Array(&A_m3, I_RECS, I_LVLS, I_LATS, I_LONS);
	Create4D_Array(&A_m4, I_RECS, I_LVLS, I_LATS, I_LONS);
	Create4D_Array(&A_m5, I_RECS, I_LVLS, I_LATS, I_LONS);
	Create4D_Array(&A_m6, I_RECS, I_LVLS, I_LATS, I_LONS);

 	Assign_Data_malloc adm;
    adm.assign_data(&A_m1,I_RECS, I_LVLS, I_LATS, I_LONS );
    adm.assign_data(&A_m2,I_RECS, I_LVLS, I_LATS, I_LONS );
    adm.assign_data(&A_m3,I_RECS, I_LVLS, I_LATS, I_LONS );
    adm.assign_data(&A_m4,I_RECS, I_LVLS, I_LATS, I_LONS );
    adm.assign_data(&A_m5,I_RECS, I_LVLS, I_LATS, I_LONS );
    adm.assign_data(&A_m6,I_RECS, I_LVLS, I_LATS, I_LONS );
    
    auto end_malloc = std::chrono::steady_clock::now();
	
	auto start_boost = std::chrono::steady_clock::now();

  // Create a 3D array that is 3 x 4 x 2
  typedef boost::multi_array<double, 4> array_type1;
  typedef boost::multi_array<double, 4> array_type2;
  typedef boost::multi_array<double, 4> array_type3;
  typedef boost::multi_array<double, 4> array_type4;
  typedef boost::multi_array<double, 4> array_type5;
  typedef boost::multi_array<double, 4> array_type6;
  typedef array_type1::index index;
  typedef array_type2::index index;
  typedef array_type3::index index;
  typedef array_type4::index index;
  typedef array_type5::index index;
  typedef array_type6::index index;
  array_type1 A1(boost::extents[I_RECS][I_LVLS][I_LATS][I_LONS]);
  array_type2 A2(boost::extents[I_RECS][I_LVLS][I_LATS][I_LONS]);
  array_type3 A3(boost::extents[I_RECS][I_LVLS][I_LATS][I_LONS]);
  array_type4 A4(boost::extents[I_RECS][I_LVLS][I_LATS][I_LONS]);
  array_type5 A5(boost::extents[I_RECS][I_LVLS][I_LATS][I_LONS]);
  array_type6 A6(boost::extents[I_RECS][I_LVLS][I_LATS][I_LONS]); 
    

	Assign_Data_boost ad;
    ad.assign_data(A1,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(A2,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(A3,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(A4,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(A5,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(A6,I_RECS, I_LVLS, I_LATS, I_LONS );
    
    
    auto end_boost = std::chrono::steady_clock::now();

    std::cout << "Elapsed time in nanoseconds for boost usage : "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end_boost - start_boost).count()
            << " ns" << std::endl;
            
    std::cout << "Elapsed time in nanoseconds for malloc usage : "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end_malloc - start_malloc).count()
            << " ns" << std::endl;

	return 0 ;
}
