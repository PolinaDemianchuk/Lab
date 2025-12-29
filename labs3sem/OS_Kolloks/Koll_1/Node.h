#pragma once
struct Node
{
    int data;
    Node* next;
    Node(int a) : data(a), next(nullptr) {}
};