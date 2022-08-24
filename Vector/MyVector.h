#pragma once
#include <algorithm>
#include <initializer_list>

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
        ~iterator()
        {
            delete array;
        }
        
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
        
        T& operator*()
        {
            return array[pos];
        }
        
        /**
         pos로 비교하지 않은 이유는
         각각 다른 vector의 iterator들끼리 pos가 같을 수 있기 때문.
         */
        bool operator==(const iterator& iter)
        {
            return &array[pos] == &iter.array[iter.pos];
        }
        
        bool operator!=(const iterator& iter)
        {
            return &array[pos] != &iter.array[iter.pos];
        }
    };
    
private:
    T * array;
    size_t vectorSize;
    size_t vectorCapacity;

public:
    MyVector(size_t defaultCapacity = 0)
    : array(new T[defaultCapacity]), vectorSize(0), vectorCapacity(defaultCapacity) {}
    
    MyVector(std::initializer_list<T> list)
    : array(new T[list.size()]), vectorSize(list.size()), vectorCapacity(list.size())
    {
        std::copy(list.begin(), list.end(), array);
    }
    
    ~MyVector()
    {
        delete[] array;
    }
    
    T& operator[](size_t pos)
    {
        return array[pos];
    }
    
    MyVector<T>& operator=(MyVector& target)
    {
        if (this != &target)
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
        assert(vectorSize != 0);
        
        return array[0];
    }
    
    T& back()
    {
        assert(vectorSize != 0);
        
        return array[vectorSize-1];
    }
    
    void push_back(T var)
    {
        if (vectorSize >= vectorCapacity)
        {
            vectorCapacity == 0 ? ++vectorCapacity : vectorCapacity *= 2;
            
            reserve(vectorCapacity);
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
    
    iterator insert(const iterator& iter,  T var)
    {
        if (vectorSize >= vectorCapacity)
        {
            reserve(vectorCapacity == 0 ? vectorCapacity + 1: vectorCapacity * 2);
        }
        
        memmove(&array[iter.pos+1], &array[iter.pos], sizeof(T) * (vectorSize - iter.pos));
        array[iter.pos] = var;
        ++vectorSize;
        
        return iterator(array, iter.pos);
    }
    
    iterator insert(const iterator& iter, std::initializer_list<T> list)
    {
        if (vectorSize + list.size() > vectorCapacity)
        {
            reserve(vectorSize + list.size());
        }

        memmove(&array[iter.pos + list.size()], &array[iter.pos], sizeof(T) * (vectorSize - iter.pos));
        std::copy(list.begin(), list.end(), &array[iter.pos]);

        vectorSize += list.size();

        return iterator(array, iter.pos);
    }
    
    /**
     memmove와 memcpy는 같은 기능
     memmove는 복사하고자 하는 부분은 buffer에 올렸다가, buffer의 값을 원하는 위치에 복사시킴.
     memcpy는 buffer에 올리지 않고 바로 복사.
     */
    iterator insert(const iterator& iter, const iterator& startIter, const iterator& endIter)
    {
        size_t insertSize = endIter.pos - startIter.pos;
        
        if (vectorSize + insertSize > vectorCapacity)
        {
            reserve(vectorSize + insertSize);
        }
        
        memmove(&array[iter.pos + insertSize], &array[iter.pos], sizeof(T) * (vectorSize - iter.pos));
        memmove(&array[iter.pos], startIter.array, sizeof(T) * insertSize);
//        memcpy(&array[iter.pos], startIter.array, sizeof(T) * insertSize);
        
        vectorSize += insertSize;
        
        return iterator(array, iter.pos);
    }
    
    /**
     삭제하고자 하는 iterator가 vector 내부인지 확인 후
     vector 내부이면 삭제
     */
    iterator erase(iterator iter)
    {
        assert(iter.pos >= 0 && iter.pos < vectorSize);
        
        memmove(&array[iter.pos], &array[iter.pos+1], sizeof(T) * (vectorSize - iter.pos - 1));
        
        vectorSize--;
       
        return end();
    }
    
    void reserve(size_t cap)
    {
        if (cap <= vectorCapacity)
        {
            return;
        }
        
        vectorCapacity = cap;
        T* newArr = new T[vectorCapacity];

        memcpy(newArr, array, sizeof(T) * vectorSize);
        
        delete[] array;

        array = newArr;
    }
    
    void resize(size_t newSize, T var = 0)
    {
        if (newSize <= vectorSize)
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
        array = &startItor.array[startItor.pos];
        vectorSize = endItor.pos - startItor.pos;
    }
    
    void assign(const size_t count, const int var)
    {
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
        return vectorSize == 0;
    }
};
