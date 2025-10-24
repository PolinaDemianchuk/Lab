#pragma once

#include <windows.h>
#include <iostream>
#include <mutex>
extern HANDLE* hOutEvent;
extern HANDLE hStartEvent;
extern HANDLE hContinueSemaphore;
extern HANDLE hRemoveEvent;
extern volatile int n;
extern volatile int remain;
extern int* arr;
extern std::mutex Mutex;
void makeElementsZeros(int* arr, int size, int Id);
void printArr(const int* arr, int size);
bool IsMarkable(int* arr, int ind);
DWORD WINAPI marker(LPVOID param);