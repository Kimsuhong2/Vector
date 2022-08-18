#pragma once
#include <stdio.h>
#include <algorithm>

template <typename T>
class MyVector
{
public:
    class iterator
    {
    private:
        friend class MyVector;
        T* array;
        size_t pos;
        
    public:
        iterator(T* ptr = nullptr, size_t index = 0) : array(ptr), pos(index) {}
        ~iterator(){}
        
        iterator& operator++()
        {
            ++pos;
            return *this;
        }
        
        iterator& operator--()
        {
            --pos;
            return *this;
        }
        
        iterator operator+(const size_t n)
        {
            return iterator(array, pos + n);
        }
        
        iterator operator-(const size_t n)
        {
            return iterator(array, pos - n);
        }
        
    };
    
private:
    T * array;
    size_t vectorSize;
    size_t vectorCapacity;

public:
    MyVector()
    : array(new T[1]), vectorSize(0), vectorCapacity(1) {}
    
    template <typename... _Args>
    MyVector(_Args&&... args) : array(new T[sizeof...(args)]), vectorSize(0), vectorCapacity(sizeof...(args))
    {
        push_back(args...);
    }
    
    MyVector(MyVector& target) : array(new T[target.capacity()]), vectorSize(0), vectorCapacity(target.capacity())
    {
        
    }
    
    ~MyVector(){}
    
    T& operator[](size_t pos)
    {
        return array[pos];
    }
    
    MyVector<T>& operator=(MyVector& target)
    {
        if(this != &target)
        {
            MyVector temp(target);
            swap(temp);
        }
        
        return *this;
    }
    
public:
    size_t size()
    {
        return vectorSize;
    }
    
    size_t capacity()
    {
        return vectorCapacity;
    }
    
    iterator begin()
    {
        return iterator(array);
    }
    
    iterator end()
    {
        return iterator(array, vectorSize);
    }
    
    T& front()
    {
        return array[0];
    }
    
    T& back()
    {
        return array[vectorSize-1];
    }
    
    template <typename... _Args>
    void push_back(T var, _Args&&... args)
    {
        push_back(var);
        push_back(args...);
    }
    
    void push_back(T var)
    {
        if (vectorSize >= vectorCapacity)
        {
            vectorCapacity *= 2;
            
            T* newArr = new T[vectorCapacity];
            
            memcpy(newArr, array, sizeof(T) * vectorSize);
            
            delete[] array;

            array = newArr;
        }
        
        array[vectorSize] = var;
        vectorSize++;
    }
    
    void pop_back()
    {
        if (vectorSize <= 0)
        {
            return;
        }
        
        --vectorSize;
    }
    
    iterator insert(const iterator& itor,  T var)
    {
        if (vectorSize >= vectorCapacity)
        {
            vectorCapacity *= 2;
            T* newArr = new T[vectorCapacity];
            
            memcpy(newArr, array, sizeof(T) * vectorSize);
            
            delete[] array;
            
            array = newArr;
        }
        
        memcpy(&array[itor.pos+1], &array[itor.pos], sizeof(T) * (vectorSize - itor.pos));
        array[itor.pos] = var;
        ++vectorSize;
        
        return itor;
    }
    
    iterator erase(const iterator& itor)
    {
        vectorSize--;
        
        memcpy(&array[itor.pos], &array[itor.pos+1], sizeof(T) * (vectorSize - itor.pos));
        
        return end();
    }
    
    void reserve(size_t cap)
    {
        if(cap <= vectorCapacity)
        {
            return;
        }
        
        vectorCapacity = cap;
        T* newArr = new T[vectorCapacity];

        memmove(newArr, array, sizeof(T) * vectorSize);
        
        delete[] array;

        array = newArr;
    }
    
    void resize(size_t newSize, T var = 0)
    {
        if(newSize <= vectorSize)
        {
            vectorSize = newSize;
            return;
        }
        
        reserve(newSize);
        
        std::fill_n(&array[vectorSize], newSize-vectorSize, var);
        
        vectorSize = newSize;
    }
    
    void assign(const iterator& startItor, const iterator& endItor)
    {
        vectorSize = endItor.pos - startItor.pos;
        
        memcpy(array, &startItor.array[startItor.pos], sizeof(T) * vectorSize);
    }
    
    void assign(const size_t count, const int var)
    {
        empty();
        
        vectorSize = count;
        
        std::fill_n(array, vectorSize, var);
    }
    
    void swap(MyVector<T>& target)
    {
        std::swap(array, target.array);
        std::swap(vectorSize, target.vectorSize);
        std::swap(vectorCapacity, target.vectorCapacity);
    }
    
    void clear()
    {
        vectorSize = 0;
    }
    
    bool empty()
    {
        if (vectorSize == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
