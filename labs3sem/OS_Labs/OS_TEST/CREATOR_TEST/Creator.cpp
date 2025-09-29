#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "Employee.h"
#include <vector>
#include <algorithm>


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        _cputs("Information doesn't match");
        _cputs("Press any key to finish...");
        _getch();
        return 1;
    }

    char* filename = argv[1];
    int num = atoi(argv[2]);

    if (num <= 0)
    {
        _cputs("Error: Number of employees must be positive\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 1;
    }

    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        _cputs("Error: Could not create file\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return 1;
    }

    _cputs("Please enter employee data:\n");
    std::vector<employee> employees;

    for (int i = 0; i < num; i++)
    {
        employee emp;
        _cprintf("Record %d:\n", i + 1);

        _cputs("Enter employee number: ");
        std::cin >> emp.num;
        std::cin.ignore();

        _cputs("Enter employee name: ");
        std::cin.getline(emp.name, sizeof(emp.name));

        _cputs("Enter hours worked: ");
        std::cin >> emp.hours;

        employees.push_back(emp);
        _cprintf("Success!\n");
    }

    std::sort(employees.begin(), employees.end(),
        [](const employee& a, const employee& b) {
            return std::strcmp(a.name, b.name) < 0;
        });

    for (const auto& emp : employees)
    {
        file.write((char*)(&emp), sizeof(struct employee));
    }
    file.close();

    _cprintf("\nFile %s created successfully with %d records.\n", filename, num);
    _cputs("Press any key to finish.\n");
    _getch();

    return 0;
}
