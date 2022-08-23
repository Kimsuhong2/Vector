#pragma once
#include "MyDoubleLinkedList.h"
#include "Node.h"
#include <iostream>

template <typename T>
class MyDoubleLinkedList
{
public:
    class iterator
    {
    private:
        friend class MyDoubleLinkedList;
        Node<T>* target;
        Node<T>* prev;
        Node<T>* next;

    public:
        iterator(Node<T>* ptr, Node<T>* prevNode = nullptr) : target(ptr), prev(prevNode) {}
        ~iterator(){}

        iterator& operator++()
        {
            if (target == nullptr)
            {
                target = next;
            }
            else
            {
                prev = target;
                target = target->next;
            }
        
            return *this;
        }

        iterator& operator--()
        {
            if (target == nullptr)
            {
                target = prev;
            }
            else
            {
                next = target;
                target = target->prev;
            }

            return *this;
        }

        T operator*()
        {
            return target->data;
        }

        bool operator==(const iterator it)
        {
            return target == it.target;
        }

        bool operator!=(const iterator& it)
        {
            return target != it.target;
        }
    };

private:
    Node<T>* head;
    Node<T>* tail;
    size_t listSize;
public:
    MyDoubleLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}
    MyDoubleLinkedList(T var) : head(new Node<T>(var)), tail(head), listSize(1) {}
    MyDoubleLinkedList(std::initializer_list<T> datas) : head(nullptr), tail(nullptr), listSize(0)
    {
        typename std::initializer_list<T>::iterator iter = datas.begin();

        while (iter != datas.end())
        {
            push_back(*iter);
            iter++;
        }
    }

private:
    /**
     빈 list에 처음 값을 넣을 때 사용 되는 함수
     head랑 tail이 새로 추가 된 node를 가리킴
     */
    void pushFirst (T data)
    {
        Node<T>* newNode = new Node(data);

        head = newNode;
        tail = newNode;
        listSize++;
    }

    /**
     인자로 넘겨받은 두 Node를 연결시켜주는 함수
     */
    void linkNode(Node<T>* prevPtr, Node<T>* nextPtr)
    {
        prevPtr->next = nextPtr;
        nextPtr->prev = prevPtr;
    }

public:
    size_t size()
    {
        return listSize;
    }

    void clear()
    {
        if (listSize == 0)
            return;
        
        if (listSize > 1)
        {
            while (listSize > 1)
            {
                pop_front();
            }
        }
        
        delete tail;
        
        head = nullptr;
        tail = nullptr;
        listSize = 0;
    }

    bool empty()
    {
        return listSize == 0;
    }

    iterator begin()
    {
        return iterator(head);
    }

    iterator end()
    {
        if (tail == nullptr)
        {
            return iterator(nullptr);
        }

        return iterator(tail->next, tail);
    }

    T front()
    {
        assert(listSize != 0);
        
        return head->data;
    }

    T back()
    {
        assert(listSize != 0);
        
        return tail->data;
    }

    void push_front(T data)
    {
        if (listSize == 0)
        {
            pushFirst(data);

            return;
        }

        Node<T>* newNode = new Node(data);

        linkNode(newNode, head);

        head = newNode;

        listSize++;
    }

    void push_back(T data)
    {
        if (listSize == 0)
        {
            pushFirst(data);

            return;
        }

        Node<T>* newNode = new Node(data);

        linkNode(tail, newNode);

        tail = newNode;

        listSize++;
    }

    void pop_front()
    {
        if (listSize == 1)
        {
            clear();
            return;
        }

        head = head->next;
        delete head->prev;
        head->prev = nullptr;
        listSize--;
    }

    void pop_back()
    {
        if (listSize == 1)
        {
            clear();
            return;
        }

        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        listSize--;
    }

    iterator insert(iterator iter, std::initializer_list<T> datas)
    {
        typename std::initializer_list<T>::iterator initializerIter = datas.end();

        while (true)
        {
            --initializerIter;
            iter = insert(iter, *initializerIter);

            if (initializerIter == datas.begin())
            {
                break;
            }
        }

        return iter;
    }

    iterator insert(iterator iter, T data)
    {
        if (iter == begin())
        {
            push_front(data);
            return iterator(head);
        }
        else if (iter == end())
        {
            push_back(data);
            return iterator(tail);
        }

        Node<T>* newNode = new Node(data);

        linkNode(iter.target->prev, newNode);
        linkNode(newNode, iter.target);

        listSize++;

        return iterator(newNode);
    }

    iterator erase(iterator iter)
    {
        if (iter.target == head)
        {
            iter.target = head->next;
            pop_front();
            return iter;
        }
        else if (iter.target == tail)
        {
            pop_back();
            iter = end();
            return --iter;
        }

        linkNode(iter.target->prev, iter.target->next);
        iter.target = iter.target->next;
        listSize--;
        return iter;
    }

    void remove(T data)
    {
        iterator iter = begin();

        while (iter != end())
        {
            if (iter.target->data == data)
            {
                iter = erase(iter);
                continue;
            }

            ++iter;
        }
    }

    void reverse()
    {
        iterator iter = begin();
        iterator endIter = end();

        while (iter != endIter)
        {
            std::swap(iter.target->next, iter.target->prev);
            --iter;
        }

        std::swap(head, tail);
    }

    void resize(size_t newSize)
    {
        if(listSize == newSize)
            return;

        if (listSize < newSize)
        {
            while (listSize < newSize)
                push_back(0);

            return;
        }

        while (listSize > newSize)
        {
            pop_back();
        }
    }
};
