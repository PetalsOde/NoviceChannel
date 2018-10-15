#include <iostream>
#include <stdio.h>
#include "Rectangle.h"
#include "Cost.h"
#include "CostDiff.h"
#include "PassinPass.h"
#include "LoopPass.h"

using namespace std;

int main()
{
	int N = 10;
	float dfi[N];
	LoopPass loopp;
	loopp.get_array_result(N, 2.89, 2.89, dfi);
	
	return 0;
}

