#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include "Employee.h"

const int ReadStart = 1;
const int ReadEnd = 2;
const int WriteStart = 3;
const int WriteEnd = 4;
const int Exit = 5;
const int Success = 6;
const int Fail = 7;

Employee* emps;
int empsNum = 0;

HANDLE* hRecordSemaphores;
HANDLE* hReaderCountMutexes;
int* readerCounts;

std::string filename;

int FindByID(int id) 
{
    for (int i = 0; i < empsNum; i++)
    {
        {
            if (emps[i].num == id)
                return i;
        }
    }
    return -1;
}
void SaveToFile();

DWORD WINAPI ClientHandles(LPVOID param)
{
    HANDLE hPipe = (HANDLE)param;
    DWORD bytesRead, bytesWritten;
    bool running = true;

    while (running)
    {
        int cmd;
        if (!ReadFile(hPipe, &cmd, sizeof(int), &bytesRead, NULL))
        {
            std::cout << "Client disconnected. Thread ending." << std::endl;
            break;
        }

        if (cmd == ReadStart)
        {
            int reqID;
            ReadFile(hPipe, &reqID, sizeof(int), &bytesRead, NULL);

            int idx = FindByID(reqID);
            if (idx == -1)
            {
                int response = Fail;
                WriteFile(hPipe, &response, sizeof(int), &bytesWritten, NULL);
                continue;
            }

            WaitForSingleObject(hReaderCountMutexes[idx], INFINITE);
            readerCounts[idx]++;
            if (readerCounts[idx] == 1)
            {
                WaitForSingleObject(hRecordSemaphores[idx], INFINITE);
            }
            ReleaseMutex(hReaderCountMutexes[idx]);

            int response = Success;
            WriteFile(hPipe, &response, sizeof(int), &bytesWritten, NULL);
            WriteFile(hPipe, &emps[idx], sizeof(Employee), &bytesWritten, NULL);

            int finishCmd = -1;
            ReadFile(hPipe, &finishCmd, sizeof(int), &bytesRead, NULL);

            WaitForSingleObject(hReaderCountMutexes[idx], INFINITE);
            readerCounts[idx]--;
            if (readerCounts[idx] == 0)
            {
                ReleaseSemaphore(hRecordSemaphores[idx], 1, NULL);
            }
            ReleaseMutex(hReaderCountMutexes[idx]);
        }
        else if (cmd == WriteStart)
        {
            int reqID;
            ReadFile(hPipe, &reqID, sizeof(int), &bytesRead, NULL);

            int idx = FindByID(reqID);
            if (idx == -1)
            {
                int response = Fail;
                WriteFile(hPipe, &response, sizeof(int), &bytesWritten, NULL);
                continue;
            }

            WaitForSingleObject(hRecordSemaphores[idx], INFINITE);

            int response = Success;
            WriteFile(hPipe, &response, sizeof(int), &bytesWritten, NULL);
            WriteFile(hPipe, &emps[idx], sizeof(Employee), &bytesWritten, NULL);

            Employee newData;
            if (ReadFile(hPipe, &newData, sizeof(Employee), &bytesRead, NULL))
            {
                emps[idx] = newData;
                std::cout << "Record " << newData.num << " updated." << std::endl;
                SaveToFile();
            }
            else 
            {
                std::cout << "Failed to read updated data from client." << std::endl;
            }

            int finishCmd;
            ReadFile(hPipe, &finishCmd, sizeof(int), &bytesRead, NULL);

            ReleaseSemaphore(hRecordSemaphores[idx], 1, NULL);
        }
        else if (cmd == Exit)
        {
            std::cout << "Client has cut the connection." << std::endl;
            running = false;
            break;
        }
        else
        {
            std::cout << "Unknown command: " << cmd << std::endl;
        }
    }

    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    return 0;
}

void SaveToFile() 
{
    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
    if (!out) 
    {
        std::cout << "Cannot open file: " << filename << std::endl;
        return;
    }
    out.write((char*)emps, sizeof(Employee) * empsNum);
    out.close();
}

int main()
{
    std::cout << "Enter bin file name: ";
    std::cin >> filename;

    std::cout << "Enter number of employees: ";
    std::cin >> empsNum;
    emps = new Employee[empsNum];

    for (int i = 0; i < empsNum; i++)
    {
        std::cout << "Employee " << i + 1 << " (ID name hours): ";
        std::cin >> emps[i].num >> emps[i].name >> emps[i].hours;
    }

    SaveToFile();

    std::cout << "File content:"<<std::endl;
    for (int i = 0; i < empsNum; i++) 
    {
        std::cout << emps[i].num << " " << emps[i].name << " " << emps[i].hours << std::endl;
    }

    int clientsNum;
    std::cout << "Enter number of clients: "<<std::endl;
    std::cin >> clientsNum;

    hRecordSemaphores = new HANDLE[empsNum];
    hReaderCountMutexes = new HANDLE[empsNum];
    readerCounts = new int[empsNum];

    for (int i = 0; i < empsNum; ++i) 
    {
        hRecordSemaphores[i] = CreateSemaphore(NULL, 1, 1, NULL);
        hReaderCountMutexes[i] = CreateMutex(NULL, FALSE, NULL);
        readerCounts[i] = 0;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdLine[] = L"Client.exe";

    for (int i = 0; i < clientsNum; i++) 
    {
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        if (!CreateProcess(NULL, cmdLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
        {
            std::cout << "Failed to start Client process" << GetLastError() << std::endl;
        }
        else 
        {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    }

    std::vector<HANDLE> hThreads;
    const wchar_t* pipeName = L"\\\\.\\pipe\\MyPipe";
    char c;
    for (int i = 0; i < clientsNum; i++) 
    {
        HANDLE hPipe = CreateNamedPipeW(
            pipeName,
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            clientsNum,
            0, 0,
            INFINITE, NULL);

        if (hPipe == INVALID_HANDLE_VALUE) 
        {
            std::cerr << "Creation of the named pipe failed." << std::endl
                << "The last error code: " << GetLastError() << std::endl;
            std::cout << "Press any char to finish server: ";
            std::cin >> c;
            return 0;
        }

        if (ConnectNamedPipe(hPipe, NULL))
        {
            std::cout << "Client connected." << std::endl;
            HANDLE hThread = CreateThread(NULL, 0, ClientHandles, (LPVOID)hPipe, 0, NULL);
            if (hThread)
            {
                hThreads.push_back(hThread);
            }
            else
            {
                std::cout << "Thread creation failed: " << GetLastError() << std::endl;
                CloseHandle(hPipe);
            }
        }
        else
        {
            std::cout << "connection failed: " << GetLastError() << std::endl;
            CloseHandle(hPipe);
        }
    }

    if (!hThreads.empty()) 
    {
        WaitForMultipleObjects((DWORD)hThreads.size(), hThreads.data(), TRUE, INFINITE);
    }

    for (HANDLE h : hThreads) CloseHandle(h);

    std::cout << "Final content"<<std::endl;
    for (int i = 0; i < empsNum; i++) 
    {
        std::cout << emps[i].num << " " << emps[i].name << " " << emps[i].hours << std::endl;
    }

    SaveToFile();

    std::string cmd;
    std::cout << "Type 'exit' to close server: ";
    while (true) 
    {
        std::cin >> cmd;
        if (cmd == "exit") break;
    }

    for (int i = 0; i < empsNum; i++) 
    {
       CloseHandle(hRecordSemaphores[i]);
       CloseHandle(hReaderCountMutexes[i]);
    }
    delete[] hRecordSemaphores;
    delete[] hReaderCountMutexes;
    delete[] readerCounts;
    delete[] emps;

    std::cout << "Server exiting." << std::endl;
    return 0;
}



