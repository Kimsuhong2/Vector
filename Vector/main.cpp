
#include "main.h"

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include "MyVector.h"
#include "QuickSort.h"
#include "MyDoubleLinkedList.h"

using namespace std;

template <typename T>
void print(list<T> li)
{
    typename list<T>::iterator iter = li.begin();
    
    while (iter != li.end())
    {
        cout << *iter << endl;
        
        iter++;
    }
}

template <typename T>
void print(MyDoubleLinkedList<T> li)
{
    typename MyDoubleLinkedList<T>::iterator iter = li.begin();
    
    while (iter != li.end())
    {
        cout << *iter << endl;
        
        ++iter;
    }
}

int main(int argc, const char* argv[])
{
}
