#include <windows.h>
#include <iostream>
#include "Elements.h"

HANDLE* hOutEvent;
HANDLE hStartEvent;
HANDLE hContinueSemaphore;
HANDLE hRemoveEvent;
std::mutex Mutex;
volatile int n;
volatile int remain;
int* arr;

void makeElementsZeros(int* arr, int size, int Id)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == Id)
        {
            arr[i] = 0;
        }
    }
}

void printArr(const int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

bool IsMarkable(int* arr, int ind)
{
    return arr[ind] == 0;
}


DWORD WINAPI marker(LPVOID param)
{
    int num = (int)param;

    WaitForSingleObject(hStartEvent, INFINITE);

    int k = 0;
    srand(num);

    while (true)
    {
        int index = rand() % n;
        Mutex.lock();
            
            if (IsMarkable(arr, index))
            {
                Sleep(5);
                arr[index] = num;
                k++;
                Sleep(5);
                Mutex.unlock();

            }
            else
            {
                Mutex.unlock();
                std::cout << num << " " << k << " " << index << std::endl;


                SetEvent(hOutEvent[num - 1]);

                WaitForSingleObject(hRemoveEvent, INFINITE);

                if (remain == num)
                {
                    makeElementsZeros(arr, n, num);
                    break;
                }
                else
                {
                    ResetEvent(hOutEvent[num - 1]);
                    WaitForSingleObject(hContinueSemaphore, INFINITE);
                }
            }
        
    }

    SetEvent(hOutEvent[num - 1]);
    return 0;
}