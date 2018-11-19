#include <iostream>
#include <chrono>

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


class Assign_Data
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

                        //      std::cout<<"arr["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"] =  "<<p[i][j][k][l] << '\n' ;
                        }
                        *arr = p;
                };
};

int main()
{
        auto start = std::chrono::steady_clock::now();

        int  I_LATS, I_LONS, I_LVLS, I_RECS;
        I_LATS = 73, I_LONS = 144 , I_LVLS = 17, I_RECS = 7300 ;

        double ****A1 = NULL;
        double ****A2 = NULL;
        double ****A3 = NULL;
        double ****A4 = NULL;
        double ****A5 = NULL;
        double ****A6 = NULL;

        Create4D_Array(&A1, I_RECS, I_LVLS, I_LATS, I_LONS);
        Create4D_Array(&A2, I_RECS, I_LVLS, I_LATS, I_LONS);
        Create4D_Array(&A3, I_RECS, I_LVLS, I_LATS, I_LONS);
        Create4D_Array(&A4, I_RECS, I_LVLS, I_LATS, I_LONS);
        Create4D_Array(&A5, I_RECS, I_LVLS, I_LATS, I_LONS);
        Create4D_Array(&A6, I_RECS, I_LVLS, I_LATS, I_LONS);

        Assign_Data ad;
    ad.assign_data(&A1,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(&A2,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(&A3,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(&A4,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(&A5,I_RECS, I_LVLS, I_LATS, I_LONS );
    ad.assign_data(&A6,I_RECS, I_LVLS, I_LATS, I_LONS );


    auto end = std::chrono::steady_clock::now();

    std::cout << "Elapsed time in nanoseconds : "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
            << " ns" << std::endl;





    return 0 ;
}

                                                     
