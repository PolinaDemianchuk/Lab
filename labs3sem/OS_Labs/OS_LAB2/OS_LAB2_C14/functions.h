#pragma once
#include "ArrInfo.h"
#include <windows.h>
#include <memory>
void min_max(arrInfo* info);
void average(arrInfo* info);
void PrintArr(std::unique_ptr<int[]>& arr, int size);
void InputArr(std::unique_ptr<int[]>& arr, int size);
void ChangeMinMaxToAverage(std::unique_ptr<int[]>& arr, int size, volatile int min, volatile int max, volatile double average);