#include <iostream>
#include <windows.h>
#include "Employee.h"

const int ReadStart = 1;
const int ReadEnd = 2;
const int WriteStart = 3;
const int WriteEnd = 4;
const int Exit = 5;
const int Success = 6;
const int Fail = 7;


void PrintEmp(const Employee& e)
{
    std::cout << "ID: " << e.num << ", name: " << e.name << ", hours: " << e.hours << std::endl;
}

int main() 
{
    HANDLE hPipe;
    const wchar_t* pipeName = L"\\\\.\\pipe\\MyPipe";
    char c;
    while (true) 
    {
        hPipe = CreateFileW(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

        if (hPipe == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Connection with the named pipe failed." << std::endl
                << "The last error code: " << GetLastError() << std::endl;
            std::cout << "Press any char to finish the client: ";
            std::cin >> c;
            return 0;
        }
        else
        {
            break;
        }
    }

    std::cout << "Connected to server" << std::endl;

    while (true)
    {
        std::cout << "1. Read\n2. Modify\n3. Exit\nYour choice: ";
        int choice;
        std::cin >> choice;
        DWORD bytesWritten, bytesRead;

        if (choice == 1)
        {
            int id;
            std::cout << "Enter Employee ID: ";
            std::cin >> id;

            int cmd = ReadStart;
            WriteFile(hPipe, &cmd, sizeof(int), &bytesWritten, NULL);
            WriteFile(hPipe, &id, sizeof(int), &bytesWritten, NULL);

            int resp;
            if (ReadFile(hPipe, &resp, sizeof(int), &bytesRead, NULL) && resp == Success) 
            {
                Employee e;
                ReadFile(hPipe, &e, sizeof(Employee), &bytesRead, NULL);
                std::cout << "READING..."<<std::endl;
                PrintEmp(e);
                std::string finishCmd;
                std::cout << "Type any letter to finish reading: ";
                std::cin >> finishCmd;
                cmd = ReadEnd;
                WriteFile(hPipe, &cmd, sizeof(int), &bytesWritten, NULL);
                std::cout << "Unlocked." << std::endl;
            }
            else 
            {
                std::cout << "Employee not found" << std::endl;
            }
        }

        if (choice == 2) 
        {
            int id;
            std::cout << "Enter employee ID: ";
            std::cin >> id;
            int cmd = WriteStart;
            WriteFile(hPipe, &cmd, sizeof(int), &bytesWritten, NULL);
            WriteFile(hPipe, &id, sizeof(int), &bytesWritten, NULL);

            int resp;
            if (ReadFile(hPipe, &resp, sizeof(int), &bytesRead, NULL) && resp == Success)
            {
                Employee e;
                bool isCorrect = false;
                ReadFile(hPipe, &e, sizeof(Employee), &bytesRead, NULL);

                while (!isCorrect)
                {
                std::cout << "EDITING..."<<std::endl;
                std::cout << "Current data: ";
                PrintEmp(e);
                std::cout << "Enter new name: ";
                std::cin >> e.name;
                std::cout << "Enter new hours: ";
                std::cin >> e.hours;
                
                std::string choice;
                std::cout << "Are you sure the data is correct?(yes/no) ";
                std::cin >> choice;
                 if (choice == "yes")
                  {
                        std::string finishCmd;
                        std::cout << "Type any letter to send data: ";
                        std::cin >> finishCmd;


                        WriteFile(hPipe, &e, sizeof(Employee), &bytesWritten, NULL);
                        cmd = WriteEnd;
                        WriteFile(hPipe, &cmd, sizeof(int), &bytesWritten, NULL);
                        std::cout << "Everything was sent to server. You may continue" << std::endl;
                        isCorrect = true;
                  }
                else if (choice == "no")
                {
                     std::cout << "Let's try again" << std::endl;
                }

                }
            }
            else 
            {
                std::cout << "Employee not found or error." << std::endl;
            }
        }

        if (choice == 3)
        {
            int cmd = Exit;
            WriteFile(hPipe, &cmd, sizeof(int), &bytesWritten, NULL);
            break;
        }

    }

    CloseHandle(hPipe);
    return 0;
}