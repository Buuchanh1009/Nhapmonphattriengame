#include "Int1D_Customize.h"


void int_c::push(int value)
{
	arr.push_back(value);
}

vector<int> int_c::Get_Arr()
{
	return arr;
}