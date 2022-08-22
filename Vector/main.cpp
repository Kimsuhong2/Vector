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

int main(int argc, const char* argv[])
{
    list<int> myList {3};
    
    list<int>::iterator iter = myList.begin();
    list<int>::iterator iter2 = myList.end();
    
    cout << *iter << endl;
    cout << *iter2 << endl;
    
    myList.insert(iter, 1);
    myList.insert(iter2, 5);
    
    iter = ++myList.begin();
    iter2 = --myList.end();
    
    myList.insert(iter, 2);
    myList.insert(iter2, 4);
    
    iter = ++myList.begin();
    
    myList.insert(--iter, 0);
}









//int main(int argc, const char * argv[])
//{
//    //vector<int> vec {900, 5651, 1, 0, 51651, -451, 4561, 111, 123, 516, 89489, 489, 489, 8789};
//    vector<int> vec {654, 184, -842, 548, 651,1 ,23, -64 ,97 ,-63 ,-5 ,48, 6, 851};
//    int size = (int)vec.size();
//
//    int arr[size];
//
//    // vector에 값들을 추가한 후
//    // 랜덤으로 arr에 넣어줌.
//    srand((unsigned int)time(NULL));
//    for(int i = 0; i < size; i++)
//    {
//        int randomIndex = rand() % vec.size();
//        arr[i] = vec[randomIndex];
//        vec.erase(vec.begin() + randomIndex);
//    }
//
//    print(arr, size);
//
//    QuickSort(arr, 0, size-1);
//
//    print(arr, size);
//}

