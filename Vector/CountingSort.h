#pragma once
#include <iostream>
/**
 countingArr에 arr에 들어있는 값들의 개수를 세어서 넣어준다.
 countingArr의 인덱스가 arr에 들어있는 값이 되고,
 해당 인덱스에 들어있는 값이 arr에 들이있는 값의 개수가 된다.
 
    key - value 방식
 ex) arr = {5, 2, 3, 6, 7, 3, 4, 6, 9, 10}
    countingArr = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
 
    arr의 첫번째 원소는 5 → countingArr[5]++;
    arr의 두번째 원소는 2 → countingArr[2]++;
    ...
    ...
    countingArr = {0, 0, 1, 2, 1, 1, 2, 1, 0, 1, 1}
              ↑ 반대로 유추해보면
    arr에 0 = 0개, 1 = 0개, 2 = 1개, 3 = 2개 ...
 
    구한 countingArr로 누적합을 적용한다. arr[i] = arr[i] + arr[ i -1];
    위에 예시를 그대로 가져오면.
 
    누적합 하기 전 : countingArr = {0, 0, 1, 2, 1, 1, 2, 1, 0, 1, 1}
    누적합 한 후    : countingArr = {0, 0, 1, 3, 4, 5, 7, 8, 8, 9, 10}
    모든 요소에 1을 빼주면 countingArr = {-1, -1, 0, 2, 3, 4, 6, 7, 7, 8, 9}
 
    나온 결과로 배열을 정렬할 수 있다.
    countingArr의 인덱스가 arr에 들어있는 값이 되고,
    countingArr[arr[i]]의 값이 arr[i]가 들어가야 될 위치가 된다.
    ex )
    countingArr = {-1, -1, 0, 2, 3, 4, 6, 7, 7, 8, 9};
    countingArr[10] = 9 가 뜻하는 것은 10이 9번 인덱스 위치에
    countingArr[4] = 3  가 뜻하는 것은 4는 3번 인덱스 위치에
*/

void CountingSort(int* arr, int length)
{
    int max = 0;                   // 최대값을 저장할 변수.
    int* sorted = new int(length);      // 정렬된 배열을 저장할 변수.
    
    // 인자로 넘겨받은 배열중 가장 큰 값을 찾는다.
    for(int i = 0; i < length; ++i)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    
    int* countingArr = new int(max+1);  // 배열에 들어있는 값들의 개수를 저장할 변수.
    memset(countingArr, 0, sizeof(int) * (max + 1)); // 0으로 초기화.
    
    for(int i = 0; i < length; ++i)
    {
        ++countingArr[arr[i]];
    }
    
    --countingArr[0];
    for(int i = 1; i < max + 1; ++i)
    {
        countingArr[i] += countingArr[i-1];
    }
    
    for(int i = 0; i < length; ++i)
    {
        sorted[countingArr[arr[i]]] = arr[i];
        --countingArr[arr[i]];
    }
    
    memmove(arr, sorted, sizeof(int) * length);
    
    delete sorted;
    delete countingArr;
}
