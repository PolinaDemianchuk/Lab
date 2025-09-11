#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <fstream>
#include <conio.h>
#include "Employee.h"
#include <iostream>
#include <string>


int main()
{
    wchar_t filename[20];
    _cputs("Enter filename: ");
    std::wcin.getline(filename, 20);


    int numb;
    _cputs("Enter number of employees: ");
    std::cin >> numb;

    wchar_t Line[30];
    swprintf_s(Line, 30, L"Creator.exe \"%s\" %d", filename, numb);

    STARTUPINFO si;
    PROCESS_INFORMATION piCom;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&piCom, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

    _cputs("Starting...\n ");
 
    if (!CreateProcess(
        NULL,  
        Line,                
        NULL,                
        NULL,               
        FALSE,               
        CREATE_NEW_CONSOLE,  
        NULL,                
        NULL,                
        &si,
        &piCom))
    {
        _cputs("The new process is not created.\n");
        _cputs("Check a name of the process.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 0;
    }
    else
    {
        _cputs("Waiting for process to end...\n");
        WaitForSingleObject(piCom.hProcess, INFINITE);
        DWORD exitCode;
        GetExitCodeProcess(piCom.hProcess, &exitCode);

        if (exitCode == 0)
        {
            _cputs("File created successfully.\n");
          
        }

        CloseHandle(piCom.hThread);
        CloseHandle(piCom.hProcess);

    }
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open())
    {
        employee emp;
        while (file.read((char*)(&emp), sizeof(emp)))
        {
            std::wcout << emp.num << L" | " << emp.name << L" | " << emp.hours << std::endl;
        }
        file.close();
    }
    else
    {
        _cputs("Error in opening the file\n");
    }

    int money;
    _cputs("Enter payment per hour:");
    std::cin >> money;
    std::cin.ignore();

    wchar_t filenameRep[20];
    _cputs("Enter report name:");
    std::wcin.getline(filenameRep, 20);

    wchar_t Rep[40];
    swprintf_s(Rep, 40, L"Reporter.exe \"%s\" \"%s\" %d", filename, filenameRep, money);

    STARTUPINFO siRep;
    PROCESS_INFORMATION piRep;
    ZeroMemory(&siRep, sizeof(STARTUPINFO));
    ZeroMemory(&piRep, sizeof(PROCESS_INFORMATION));
    siRep.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(
        NULL,
        Rep,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &siRep,
        &piRep))
    {
        _cputs("The new process is not created.\n");
        _cputs("Check a name of the process.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 0;
    }
    else
    {
        _cputs("Waiting for process to end...\n");
        WaitForSingleObject(piRep.hProcess, INFINITE);
        DWORD exitCode;
        GetExitCodeProcess(piRep.hProcess, &exitCode);

        if (exitCode == 0)
        {
            _cputs("Report was created successfully\n");
        }

        CloseHandle(piRep.hThread);
        CloseHandle(piRep.hProcess);
    }
    _cputs("\n---- REPORT ----\n");

    std::ifstream report(filenameRep);
    if (report.is_open())
    {
        std::string line;
        while (getline(report, line))
        {
            std::cout << line << std::endl; 
        }
        report.close();
    }
    else
    {
        _cputs("Can't open the report file\n");
    }

    _cputs("Press any key to finish...\n");
    _getch();
    return 0;
}
