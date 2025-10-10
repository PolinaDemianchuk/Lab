#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include "Employee.h"
#include <cstdlib>
#include <conio.h>

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        _cputs("Press any key to finish.\n");
        _getch();
        return 1;
    }

    char* inFilename = argv[1];
    char* outFilename = argv[2];
    double payment = atoi(argv[3]);

    if (payment <= 0)
    {
        _cputs("Error: Payment must be positive number\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 1;
    }

    std::ifstream inFile(inFilename, std::ios::binary);
    if (!inFile.is_open())
    {
        _cprintf("Error: Cannot open input file\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 1;
    }

    std::ofstream outFile(outFilename);
    if (!outFile.is_open())
    {
        _cprintf("Error: Cannot create output file\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 1;
    }

    outFile << "File report \"" << inFilename << "\"" << std::endl;
    outFile << "\tIP\t | \tNAME\t | HOURS | PAYMENT" << std::endl << std::endl;

    employee emp;
    int count = 0;

    while (inFile.read((char*)(&emp), sizeof(employee)))
    {
        count++;
        double salary = emp.hours * payment;

        outFile << emp.num << "\t\t | "<< emp.name << "\t | "<< emp.hours << "\t | "<< salary << std::endl;
    }

    inFile.close();
    outFile.close();

    _cputs("Report generated successfully\n");
    _cputs("Press any key to finish.\n");
    _getch();

    return 0;
}