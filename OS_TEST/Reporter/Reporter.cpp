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

    char* infilename = argv[1];
    char* outfilename = argv[2];
    double payment = atoi(argv[3]);

    if (payment <= 0)
    {
        _cputs("Error: Payment must be positive number\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 1;
    }

    std::ifstream infile(infilename, std::ios::binary);
    if (!infile.is_open())
    {
        _cprintf("Error: Cannot open input file\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 1;
    }

    std::ofstream outfile(outfilename);
    if (!outfile.is_open())
    {
        _cprintf("Error: Cannot create output file\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 1;
    }

    outfile << "File report \"" << infilename << "\"" << std::endl;
    outfile << "\tIP\t | \tNAME\t | HOURS | PAYMENT" << std::endl << std::endl;

    employee emp;
    int count = 0;

    while (infile.read((char*)(&emp), sizeof(employee)))
    {
        count++;
        double salary = emp.hours * payment;

        outfile << emp.num << "\t\t | "<< emp.name << "\t | "<< emp.hours << "\t | "<< salary << std::endl;
    }

    infile.close();
    outfile.close();

    _cputs("Report generated successfully\n");
    _cputs("Press any key to finish.\n");
    _getch();

    return 0;
}