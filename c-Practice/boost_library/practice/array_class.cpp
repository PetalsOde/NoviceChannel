#include <iostream>
#include <chrono>
#include <boost/multi_array.hpp>

class myClass
{
public:
    myClass()
        : yourArray(boost::extents[3][3][3][3][3])
    {
        index i = 1;
        index j = 1;
        yourArray[i][j][0][0][0] = 42;
    }

    void printArray()
    {
        std::cout << yourArray[1][1][0][0][0];
    }

private:
    typedef boost::multi_array<double, 5> FiveDim;
    typedef FiveDim::index index;

    FiveDim yourArray;
};


class Assign_Data
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

                //              std::cout<<"arr["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"] =  "<<arr[i][j][k][l] << '\n' ;
                        }
                };
};

int main()
{
        auto start = std::chrono::steady_clock::now();

    myClass c;
    c.printArray();

        int  I_LATS, I_LONS, I_LVLS, I_RECS;
        I_LATS = 73, I_LONS = 144 , I_LVLS = 17, I_RECS = 7300 ;
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


        Assign_Data ad;
    ad.assign_data(A1,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(A2,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(A3,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(A4,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(A5,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(A6,I_RECS, I_LVLS, I_LATS, I_LONS );


    auto end = std::chrono::steady_clock::now();

    std::cout << "Elapsed time in nanoseconds : "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
            << " ns" << std::endl;



    return 0 ;
}
                                                                                         
