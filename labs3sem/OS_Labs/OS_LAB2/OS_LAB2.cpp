#include <windows.h>
#include <iostream>
#include <algorithm>
#include "ArrInfo.h"
#include "functions.h"

int main()
{
	int size;
	std::cout << "Enter number of elements: ";
	std::cin >> size;
	int* arr = new int[size];
	std::cout << "Enter all elements: ";

	InputArr(arr, size);

	arrInfo info;

	info.size = size;
	info.arr = arr;

	HANDLE hMinMax;
	DWORD IDThread1;

	HANDLE hAverage;
	DWORD IDThread2;

	PrintArr(info.arr, info.size);

	hMinMax = CreateThread(NULL, 0, min_max, &info, 0, &IDThread1);
	if (hMinMax == NULL)
		return GetLastError();

	hAverage = CreateThread(NULL, 0, average, &info, 0, &IDThread2);
	if (hAverage == NULL)
		return GetLastError();

	WaitForSingleObject(hMinMax, INFINITE);
	WaitForSingleObject(hAverage, INFINITE);
	CloseHandle(hMinMax);
	CloseHandle(hAverage);

	ChangeMinMaxToAverage(info.arr, info.size, info.min, info.max, info.average);
	PrintArr(info.arr, info.size);

	delete[] arr;

	return 0;
}