#include "functions.h"
#include <iostream>
#include <memory>
#include <thread>

void min_max(arrInfo *info)
{
	std::cout << "Minmax Thread is started." << std::endl;
	int min = info->arr[0];
	int max = info->arr[0];
	for (int i = 0; i < info->size; i++)
	{
		if (min > info->arr[i])
		{
			min = info->arr[i];
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(7));

		if (max < info->arr[i])
		{
			max = info->arr[i];
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(7));
	}
	std::cout << "Min elem = " << min << std::endl;
	std::cout << "Max elem = " << max << std::endl;
	info->min = min;
	info->max = max;
	std::cout << "Minmax Thread is finished." << std::endl;
}

void average(arrInfo* info)
{
	std::cout << "Average Thread is started." << std::endl;
	int sum = 0;
	for (int i = 0; i < info->size; i++)
	{
		sum += info->arr[i];
		std::this_thread::sleep_for(std::chrono::milliseconds(12));
	}
	double average = (double)sum / info->size;
	std::cout << "Average sum = " << average << std::endl;
	info->average = average;
	std::cout << "Average Thread is finished." << std::endl;
}

void PrintArr(std::unique_ptr<int[]>& arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "Element " << i + 1 << ": " << arr[i] << std::endl;
	}
}

void InputArr(std::unique_ptr<int[]>& arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cin >> arr[i];
	}
}

void ChangeMinMaxToAverage(std::unique_ptr<int[]>& arr, int size, volatile int min, volatile int max, volatile double average)
{
	for (int i = 0; i < size; i++)
	{
		if (max == arr[i] || min == arr[i])
		{
			arr[i] = average;
		}
	}
}