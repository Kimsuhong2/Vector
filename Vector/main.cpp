#include <iostream>
#include <vector>
#include "MyVector.h"

using namespace std;

// 배열 출력 함수
template <typename T>
void print(T arr[], size_t size)
{
    for(int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template<typename T>
void QuickSort(T* arr, int start, int end)
{
    // pivot을 배열 가운데 값으로 정해 줌.
    T pivot = arr[(start + end) / 2];
    int leftIter = start;
    int rightIter = end;
    
    while (leftIter < rightIter)
    {
        while(arr[leftIter] < pivot)
        {
            leftIter++;
        }
        
        while(arr[rightIter] > pivot)
        {
            rightIter--;
        }
        
        // left, right가 동시에 pivot을 가리키면 무한루프에 빠지게 됨
        // 이에 대한 예외처리.
        if(leftIter == rightIter)
        {
            leftIter++;
            rightIter--;
        }
        
        if(leftIter < rightIter)
        {
            std::swap(arr[leftIter], arr[rightIter]);
        }
    }
    
    if (start < rightIter)
    {
        QuickSort(arr, start, rightIter);
    }
    
    if (end > leftIter)
    {
        QuickSort(arr, leftIter, end);
    }
}

int main(int argc, const char * argv[])
{
    vector<int> vec { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = (int)vec.size();
    
    int arr[size];
    
    // vector에 값들을 추가한 후
    // 랜덤으로 arr에 넣어줌.
    srand((unsigned int)time(NULL));
    for(int i = 0; i < size; i++)
    {
        int randomIndex = rand() % vec.size();
        arr[i] = vec[randomIndex];
        vec.erase(vec.begin() + randomIndex);
    }
    
    print(arr, size);

    QuickSort(arr, 0, size-1);
    
    print(arr, size);
}

