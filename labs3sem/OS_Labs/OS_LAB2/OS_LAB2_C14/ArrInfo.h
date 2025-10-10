#pragma once
struct arrInfo
{
	int size;
	int* arr;
	volatile int min;
	volatile int max;
	volatile double average;
	//atomic<int>min;
};