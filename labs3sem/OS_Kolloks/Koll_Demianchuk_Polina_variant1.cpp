
#include <iostream>
#include <vector>
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

struct Node 
{
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

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
    while (head!=nullptr) 
    {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

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
    std::cout << "Enter size of array to remove duplicates: " ;
    std::cin >> size;

    dupArr.resize(size);

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
    std::cout << "Enter number of elements to reverse: ";
    std::cin >> count;

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
        newNode = new Node(numb);
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