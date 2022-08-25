#pragma once

#include <iostream>

template <typename T>
class Node
{
public:
    T data;
    Node* next;
    Node* prev;
    
public:
    Node(T var) : data(var), next(nullptr), prev(nullptr){}
    ~Node()
    {
        delete this;
    }
};
