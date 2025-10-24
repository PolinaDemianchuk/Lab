#include <windows.h>
#include <iostream>
#include "Elements.h"

int main()
{

    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;
    n = size;
    arr = new int[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = 0;
    }

    int markCount;
    std::cout << "Enter number of marker threads: ";
    std::cin >> markCount;

    HANDLE* hMarker = new HANDLE[markCount];
    DWORD* IDMarkers = new DWORD[markCount];
    hOutEvent = new HANDLE[markCount];


    hStartEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (hStartEvent == NULL)
    {
        return GetLastError();
    }

    hContinueSemaphore = CreateSemaphore(NULL, 0, markCount, NULL);

    if (hContinueSemaphore == NULL)
    {
        return GetLastError();
    }

    hRemoveEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (hRemoveEvent == NULL)
    {
        return GetLastError();
    }

    for (int i = 0; i < markCount; i++)
    {
        hMarker[i] = CreateThread(NULL, 0, marker, (LPVOID)(i + 1), 0, &IDMarkers[i]);

        hOutEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (hOutEvent[i] == NULL)
        {
            return GetLastError();
        }
    }

    SetEvent(hStartEvent);

    int activeThreads = markCount;

    while (activeThreads > 0)
    {
        WaitForMultipleObjects(markCount, hOutEvent, TRUE, INFINITE);

        std::cout << "Current array state: ";
        for (int i = 0; i < n; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;

        int NumTerminate;
        std::cout << "Enter marker number to terminate ";
        std::cin >> NumTerminate;
        remain = NumTerminate;

        SetEvent(hRemoveEvent);

        WaitForSingleObject(hMarker[NumTerminate - 1], INFINITE);

        CloseHandle(hMarker[NumTerminate - 1]);

        hMarker[NumTerminate - 1] = NULL;

        activeThreads--;

        ResetEvent(hRemoveEvent);

        std::cout << "Array after removing marker " << NumTerminate << ": ";

        printArr(arr, n);

        if (activeThreads > 0)
        {
            std::cout << "Markers remained: " << activeThreads << std::endl;
            for (int i = 0; i < markCount; i++)
            {
                if (hMarker[i] != NULL)
                {
                    ResetEvent(hOutEvent[i]);
                }
            }
            ReleaseSemaphore(hContinueSemaphore, activeThreads, NULL);
        }
    }

    std::cout << "All marker threads have been terminated." << std::endl;

    for (int i = 0; i < markCount; i++)
    {
        CloseHandle(hOutEvent[i]);
    }

    CloseHandle(hStartEvent);
    CloseHandle(hContinueSemaphore);
    CloseHandle(hRemoveEvent);

    delete[] hMarker;
    delete[] IDMarkers;
    delete[] hOutEvent;
    delete[] arr;

    return 0;
}