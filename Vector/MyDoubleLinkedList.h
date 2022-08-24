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

    public:
        iterator(Node<T>* ptr = nullptr, Node<T>* prevNode = nullptr) : target(ptr), prev(prevNode) {}
        ~iterator()
        {
            delete target;
            delete prev;
        }

        iterator& operator++()
        {
            if (target != nullptr)
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
            else if (target->prev != nullptr)
            {
                target = target->prev;
            }
            
            return *this;
        }

        T& operator*()
        {
            return target->data;
        }

        bool operator==(const iterator iter)
        {
            return target == iter.target && prev == iter.prev;
        }

        bool operator!=(const iterator& iter)
        {
            return target != iter.target && prev != iter.prev;
        }
    };

private:
    Node<T>* head;
    Node<T>* tail;
    size_t listSize;
public:
    MyDoubleLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}
    MyDoubleLinkedList(T var) : head(new Node<T>(var)), tail(head), listSize(1) {}
    MyDoubleLinkedList(std::initializer_list<T> data) : head(nullptr), tail(nullptr), listSize(0)
    {
        typename std::initializer_list<T>::iterator iter = data.begin();

        while (iter != data.end())
        {
            push_back(*iter);
            iter++;
        }
    }
    ~MyDoubleLinkedList()
    {
        clear();
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
        
        Node<T>* prevHead;
        
        while (head != nullptr)
        {
            prevHead = head;
            head = head->next;
            delete prevHead;
        }
        
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

    T& front()
    {
        assert(listSize != 0);
        
        return head->data;
    }

    T& back()
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
        assert(listSize >= 1);
        
        Node<T>* prevHead = head;
        
        if(head->next != nullptr)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
        {
            head = tail = nullptr;
        }
        
        delete prevHead;
        listSize--;
    }

    void pop_back()
    {
        assert(listSize >= 1);
        
        Node<T>* prevTail = tail;
        
        if(prevTail->prev != nullptr)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        {
            head = tail = nullptr;
        }
        
        delete prevTail;
        listSize--;
    }

    iterator insert(iterator iter, std::initializer_list<T> data)
    {
        typename std::initializer_list<T>::iterator initializerIter = data.end();

        do
        {
            --initializerIter;
            iter = insert(iter, *initializerIter);

        } while (initializerIter != data.begin());

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
        
        Node<T>* prevNode = iter.target;

        linkNode(iter.target->prev, iter.target->next);
        iter.target = iter.target->next;
        
        delete prevNode;
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
        {
            return;
        }

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
