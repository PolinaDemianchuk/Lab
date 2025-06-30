#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


double** rnd_matr(int* n, int* m); // Функция для генерации случайной матрицы

void print_matr(double** ma, int n, int m);// Функция для вывода матрицы

void delete_matr(double** ma, int n); // Функция для освобождения памяти

double** rotate_matr(double** ma, int n, int m);// Функция для поворота матрицы на 90° против часовой стрелки


// Функция для создания случайной матрицы заданного размера
double** rnd_matr(int* n, int* m)
{
    setlocale(LC_ALL, "");
    cout << "Введите количество строк: ";
    cin >> *n;
    cout << "Введите количество столбцов: ";
    cin >> *m;
    double** ma = new double* [*n]; // Создание массива указателей на строки
    for (int i = 0; i < *n; i++)
        ma[i] = new double[*m]; // Создание каждой строки матрицы

    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
            ma[i][j] = rand() / (double)100 - 100;

    return ma; // Возврат указателя на матрицу
}

// Выводим матрицу
void print_matr(double** ma, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%.2f ", ma[i][j]); // Печать элемента матрицы
        cout << endl << endl;;
    }
}

// Функция для освобождения памяти, занятой матрицей
void delete_matr(double** ma, int n)
{
    for (int i = 0; i < n; i++)
        delete[] ma[i]; // Удаление каждой строки
    delete[] ma; // Удаление массива указателей
}

// Функция для поворота матрицы на 90° против часовой стрелки
double** rotate_matr(double** ma, int n, int m)
{
    double** rotated = new double* [m]; // Создание новой матрицы для хранения результата
    for (int i = 0; i < m; i++)
        rotated[i] = new double[n]; // Создание строк для новой матрицы

    // Поворот матрицы
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            rotated[m - 1 - j][i] = ma[i][j]; // Перемещение элементов

    return rotated; // Возврат указателя на повернутую матрицу
}

int main() 
{
    srand(time(NULL)); // Инициализация генератора случайных чисел
    int n, m; 
    double** matr = rnd_matr(&n, &m); // Генерация случайной матрицы

    cout << endl << endl;

    cout << "Исходная матрица:"<<endl;
    cout << endl;
    print_matr(matr, n, m); // Вывод исходной матрицы

    cout << endl << endl;

    double** rotated_matr = rotate_matr(matr, n, m); // Поворот матрицы

    cout << "Повернутая матрица на 90° против часовой стрелки: " << endl;
    cout << endl;

    print_matr(rotated_matr, m, n); // Печать повернутой матрицы

    delete_matr(matr, n); 

    delete_matr(rotated_matr, m); // Освобождение памяти

    system("pause"); // Приостановка перед завершением программы
    return 0;
}

