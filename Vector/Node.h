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

public:
    void setNext(Node* next)
    {
        this->next = next;
    }
    
    void setPrev(Node* prev)
    {
        this->prev = prev;
    }
    
    T getData()
    {
        return data;
    }
};
