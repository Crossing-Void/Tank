#include "pch.h"
#include "lockSystem.h"

#include <math.h>


target findMin(minArray array)
{
	target result;
	result.value = array.nums[0];
	result.index = 0;
	for (int i = 1; i < array.size; i++)
	{
		if (array.nums[i] < result.value)
		{
			result.value = array.nums[i];
			result.index = i;
		}
	}
	return result;
}

trackingData lockSystem(userData tank, enemyData e[])
{
	minArray input;
	target ouput;
	trackingData data;
	for (int i = 0; i < input.size; i++)
	{
		input.nums[i] = sqrt((e[i].pos.pointX - tank.pos.pointX) * (e[i].pos.pointX - tank.pos.pointX) +
			(e[i].pos.pointY - tank.pos.pointY) * (e[i].pos.pointY - tank.pos.pointY));
		if (e[i].enable == 0)
			input.nums[i] = 9999;
	}
	ouput = findMin(input);
	data.pos.pointX = e[ouput.index].pos.pointX - tank.pos.pointX;
	data.pos.pointY = e[ouput.index].pos.pointY - tank.pos.pointY;
	data.pos.angle = atan(data.pos.pointY / data.pos.pointY);
	return data;
}
