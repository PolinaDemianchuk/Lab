#include <windows.h>
#include <iostream>
#include <algorithm>
#include "ArrInfo.h"
#include "functions.h"

using namespace std;

int main()
{
	int size;
	cout << "Enter number of elements: ";
	cin >> size;
	int* arr = new int[size];
	cout << "Enter all elements: ";
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}
	arrInfo info;
	info.size = size;
	info.arr = arr;

	HANDLE hMinMax;
	DWORD IDThread1;

	HANDLE hAverage;
	DWORD IDThread2;

	for (int i = 0; i < size; i++)
	{
		cout <<"Element "<<i+1<<": "<< arr[i]<<endl;
	}

	hMinMax = CreateThread(NULL, 0, min_max, &info, 0, &IDThread1);
	if (hMinMax == NULL)
		return GetLastError();

	hAverage = CreateThread(NULL, 0, average, &info, 0, &IDThread2);
	if (hAverage == NULL)
		return GetLastError();

	WaitForSingleObject(hMinMax, INFINITE);
	CloseHandle(hMinMax);

	WaitForSingleObject(hAverage, INFINITE);
	CloseHandle(hAverage);

	for (int i = 0; i < info.size; i++)
	{
		if (info.max == info.arr[i] || info.min == info.arr[i])
		{
			info.arr[i] = info.average;
		}
	}

	for (int i = 0; i < info.size; i++)
	{
		cout <<"New element "<<i+1<< ": "<< info.arr[i]<<endl;
	}

	return 0;
}

