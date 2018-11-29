/****************************************************************/
/** data_mem.h                      
*
*
* Created on : 29 November 2018
*
*
* 
* Author : Newbie-Coder-1105
****************************************************************/



#pragma once
#include <iostream>
#include <string>

class Data_mem 
{
	public:
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
			
		void data_storey(int &w, int &x, int &y, int &z, short *****var);
			
};
