#include <windows.h>
#include <iostream>
#include "ArrInfo.h"
#include "functions.h"
#include <memory>
#include <thread>

int main()
{
	int size;
	std::cout << "Enter number of elements: ";
	std::cin >> size;
	std::unique_ptr<int[]> arr = std::make_unique<int[]>(size);
	std::cout << "Enter all elements: ";

	InputArr(arr, size);

	arrInfo info;

	info.size = size;
	info.arr = arr.get();

	PrintArr(arr, info.size);
	std::thread MinMax(min_max, &info);
	std::thread Average(average, &info);

	MinMax.join();
	Average.join();

	ChangeMinMaxToAverage(arr, info.size, info.min, info.max, info.average);
	PrintArr(arr, info.size);

	return 0;
}