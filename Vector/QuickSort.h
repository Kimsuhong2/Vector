#pragma once

#include <iostream>

// 배열 출력 함수
template <typename T>
void print(T arr[], size_t size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void QuickSort(T* arr, int start, int end)
{
    // pivot을 배열 가운데 값으로 정해 줌.
    T pivot = arr[(start + end) / 2];
    int leftIter = start;
    int rightIter = end;

    while (leftIter < rightIter)
    {
        while (arr[leftIter] < pivot)
        {
            leftIter++;
        }

        while (arr[rightIter] > pivot)
        {
            rightIter--;
        }
        
        if (leftIter == rightIter)
        {
            leftIter++;
            rightIter--;
            continue;
        }
        
        if (leftIter < rightIter)
        {
            std::swap(arr[leftIter++], arr[rightIter--]);
        }
        print(arr, 14);
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
