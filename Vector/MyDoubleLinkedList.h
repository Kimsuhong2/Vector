#pragma once
#include "MyDoubleLinkedList.h"
#include "Node.h"
#include <iostream>

using namespace std;

template <typename T>
class MyDoubleLinkedList
{
public:
    class iterator
    {
    private:
        friend class MyDoubleLinkedList;
        Node<T>* target;
        
    public:
        iterator(Node<T>** ptr, int dir) : target(ptr)
        {
            
        }
        ~iterator(){}
        
        iterator& operator++()
        {
            target = &(*target)->next;
            return *this;
        }
        
        iterator& operator--()
        {
            target = &(*target)->prev;
            return *this;
        }
        
        T operator*()
        {
            return (*target)->getData();
        }
        
        bool operator==(const iterator it)
        {
            return &target == &it.target;
        }
        
        bool operator!=(const iterator& it)
        {
            return &target != &it.target;
        }
    };
    
private:
    Node<T>* head;
    Node<T>* tail;
    size_t listSize;
public:
    MyDoubleLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}
    MyDoubleLinkedList(T var) : head(new Node<T>(var)), tail(head), listSize(1)
    {
    };
    
public:
    size_t size()
    {
        return listSize;
    }
    
    iterator begin()
    {
        cout << "head : " << &head << endl;
        return iterator(head->prev);
    }
    
    iterator end()
    {
        return iterator(tail->next);
    }
    
    iterator insert(iterator iter, T data)
    {
        Node<T>* node = new Node(data);
        
        if (listSize == 0)
        {
            head = node;
            tail = node;
            listSize++;
            return iterator(head);
        }
        
        if (iter.target == head)
        {
            head->prev = node;
            node->next = head;
            head = node;
            listSize++;
            iter.target = node;
            return iter;
        }
        
        if (iter.target == nullptr)
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
            listSize++;
            return iterator(node);
        }
        
        iter.target->prev = node;
        node = iter.target;
        
        iter.target->prev->next = node;
        node = iter.target->prev;
        
        listSize++;
        
        return iterator(node);
    }
};
