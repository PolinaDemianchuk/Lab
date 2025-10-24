#include <iostream>
#include <vector>
#include "Funcs.h"

int main()
{
    std::vector<long long> factarr;
    int n;
    std::cout << "Enter number: ";
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        factarr.push_back(fact(i));
    }
    std::cout << "Factorials array: ";
    for (int i = 0; i < n; i++)
    {
        std::cout<< factarr[i]<< " ";
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::vector<int> dupArr;
    int size;
    try
    {
        std::cout << "Enter size of array to remove duplicates: ";
        std::cin >> size;
        if (size < 0)
        {
            throw "Number must be positive!";
        }
        dupArr.resize(size);
    }
    catch (const char* invalErr)
    {
        std::cout << "Error: " << invalErr<<std::endl;
    }
    std::cout << "Enter array: ";
   
    for (int i = 0; i < size; i++)
    {
        std::cin >> dupArr[i];
    }
    std::cout << "Array after removing duplicates: ";
    std::vector<int> result = duplicate(dupArr, size);
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << result[i] << " ";
    }

    std::cout << std::endl;
    std::cout << std::endl;

    int count;

    try
    {
        std::cout << "Enter number of elements to reverse: ";
        std::cin >> count;
        if (count < 0)
        {
            throw "Number must be positive!";
        }
    }
    catch (const char* invalErr)
    {
        std::cout << "Error: " << invalErr<<std::endl;
    }

    if (count <= 0) 
    {
        std::cout << "List is empty" << std::endl;
        return 0;
    }

    Node* head=NULL;
    Node* tail=NULL;
    Node* newNode;

    int numb;
    std::cout << "Enter numbers: ";
    for (int i = 0; i < count; i++) 
    {
        std::cin >> numb;
        newNode = new Node (numb);
        if (head == nullptr) 
        {
            head = newNode;
            tail = newNode;
        }
        else 
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    Reverse(head);
    std::cout << "Reversed List: ";
    printList(head);

    return 0;
}