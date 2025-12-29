#include <iostream>
#include <vector>
#include "Funcs.h"
#include "Node.h"

long long fact(int n)
{
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    return n * fact(n - 1);
}

std::vector<int> duplicate(std::vector<int> arr, int size)
{
    std::vector<int> modified_arr;
    bool isDuplicate;
    for (int i = 0; i < size; i++)
    {
        isDuplicate = false;
        for (int j = 0; j < modified_arr.size(); j++)
        {
            if (arr[i] == modified_arr[j])
            {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate)
        {
            modified_arr.push_back(arr[i]);
        }
    }
    return modified_arr;
}

void Reverse(Node*& head)
{
    if (head == nullptr || head->next == nullptr)
        return;

    Node* newHead = head->next;
    Reverse(newHead);
    head->next->next = head;
    head->next = nullptr;
    head = newHead;
}

void printList(Node* head)
{
    while (head != nullptr)
    {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}
