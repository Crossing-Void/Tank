#pragma once
#ifndef ddf
#include "data_format.h"
#endif // !ddf






struct minArray
{
	double nums[5];
	int size = 5;
};
struct target
{
	int index;
	double value;
};
struct trackingData
{
	struct position pos;
};
target findMin(struct minArray);
trackingData lockSystem(struct userData, struct enemyData[]);