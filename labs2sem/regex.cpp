#include <iostream>
#include <regex>
#include <string>

using namespace std;

//1234562  345670 00333 0333.1121 2424, 423423 - 1.17E-08 - 1.17E-081.17E81.17e8

//113..444
//1. - 12345
//23232312 ? 33
//1.17eE + 08 1.17EE + 08 1.17Ee + 08
//1.17Ee++8
//* 90875
//!»№; % ? *

int main() 
{
    setlocale(LC_ALL, "ru");

    regex numberr("^[+-]?(([0-9]+([\.,][0-9]*)?)|(\.[0-9]+))([eE][+-]?[0-9]+)?$");

    string text = "2424,423423";

    cout << text<<endl;


    if (regex_search(text, numberr))
        cout << "Строка соответствует шаблону" << endl;
    else
        cout << "Не соответствует" << endl;



    return 0;
}
