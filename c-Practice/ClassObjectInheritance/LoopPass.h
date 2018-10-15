#pragma once
#include <iostream>
#include <stdio.h>
#include "Rectangle.h"
#include "Cost.h"
#include "CostDiff.h"
#include "PassinPass.h"

using namespace std;

class LoopPass: public Rectangle,
				   public Cost,
				   public Costdiff,
				   public PassinPass
{
	public:
		void get_array_result(int N, float cpa1_, float cpa2_, float *df_array);
	
};
