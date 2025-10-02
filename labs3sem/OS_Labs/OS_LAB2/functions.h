#pragma once
#include "ArrInfo.h"
#include <windows.h>

    DWORD WINAPI min_max(LPVOID param);
    DWORD WINAPI average(LPVOID param);
    void PrintArr(int* arr, int size);
    void InputArr(int* arr, int size);
    void ChangeMinMaxToAverage(int* arr, int size, volatile int min, volatile int max, volatile double average);


