#include "LoopPass.h"

void LoopPass::get_array_result(int N, float cpa1_, float cpa2_, float df_array[])
{
	PassinPass passp;
	passp.setAa(2.89);
	passp.setBb(2.89);
	
//	float *p = df_array;
	
	for (int i =0; i <N; i++)
	{
		a = i + 10;
		b = i + 2;
		c = i * 2 ;
		d = i * 3 ;
		passp.setCc(a);
		passp.setDd(b);
		passp.setEe(c);
		passp.setFf(d);
		
	
		
		df_array[i] = passp.getCstDff(); 
		cout <<" object inheritance within function = "<<df_array[i] <<endl;
	
	}	
//	df_array = p;
}


