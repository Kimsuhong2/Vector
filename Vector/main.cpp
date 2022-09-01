#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <set>
#include "main.h"
#include "MyVector.h"
#include "QuickSort.h"
#include "MyDoubleLinkedList.h"
#include "MyCompleteBinaryTree.h"
#include "MyBinarySearchTree.h"
#include "MyRedBlackTree.h"
#include "MyHeapTree.h"
#include "CountingSort.h"

using namespace std;

void CBTTestCase();
void BSTTestCase();
void RBTTestCase();
void HTTestCase();

int main(int argc, const char* argv[])
{
    int arr[10] = {4, 2, 3, 5, 7, 6, 10, 9, 1, 8};
    
    CountingSort(&arr[0], 10);
    
    for(int i = 0; i < 10; ++i)
    {
        cout << arr[i] << " ";
    }
}

void CBTTestCase()
{
    MyCompleteBinaryTree<int> cbt;

    int key;
    int data;
    int index;
    int order;

    cout << "완전 이진 트리" << endl;
    
    while(true)
    {
        cout << "1. push_back(value)" << endl;
        cout << "2. pop_back()" << endl;
        cout << "3. insert(index, value)" << endl;
        cout << "4. erase(index)" << endl;
        cout << "5. 순회출력" << endl;
        cout << "6. 트리형태 출력" << endl;
        cout << "7. size()" << endl;
        cout << "8. clear()" << endl;
        cout << "9. 종료" << endl;

        cout << "키를 입력하세요 : ";
        cin >> key;
        cout << endl;

        if (key > 8)
            break;

        switch(key)
        {
            case 1:
                cout << "insert 할 값을 입력하세요 : ";
                cin >> data;
                cbt.push_back(data);
                break;
            case 2:
                cbt.pop_back();
                break;
            case 3:
                cout << "insert할 값을 입력해주세요 : ";
                cin >> data;
                cout << "insert할 위치를 입력하세요 (root = 0) : ";
                cin >> index;
                cbt.insert(index, data);
                break;
            case 4:
                cout << "erase 할 위치를 입력하세요 (root = 0) : ";
                cin >> index;
                cbt.erase(index);
                break;
            case 5:
                cout << "1.전위순회" << endl;
                cout << "2.중위순회" << endl;
                cout << "3.후위순회" << endl;
                cout << "순회 방식을 선택해주세요 : ";
                cin >> order;
                if(order == 1)
                    cbt.setTraversalOrder(cbt.PREORDER);
                else if (order == 2)
                    cbt.setTraversalOrder(cbt.INORDER);
                else
                    cbt.setTraversalOrder(cbt.POSTORDER);

                cbt.printWithTraversalOrder();
                break;
            case 6:
                cbt.printTree();
                break;
            case 7:
                cout << "size = " << cbt.size() << endl;
                break;
            case 8:
                cbt.clear();
                break;
        }
        cout << endl;
    }
}

void BSTTestCase()
{
    MyBinarySearchTree<int> bst;
    int key;
    int data;

    cout << "이진 탐색 트리" << endl;

    while(true)
    {
        cout << "1. insert(value)" << endl;
        cout << "2. erase(value)" << endl;
        cout << "3. 트리형태 출력" << endl;
        cout << "4. size() " << endl;
        cout << "5. clear() " << endl;
        cout << "6. 종료" << endl;

        cout << "키를 입력하세요 : ";
        cin >> key;
        cout << endl;
        if (key > 5)
            break;

        switch(key)
        {
            case 1:
                cout << "insert할 값을 입력하세요 : ";
                cin >> data;
                bst.insert(data);
                break;
            case 2:
                cout << "erase할 값을 입력하세요 : ";
                cin >> data;
                bst.erase(data);
                break;
            case 3:
                bst.print();
                break;
            case 4:
                cout << "size = " << bst.size() << endl;
                break;
            case 5:
                bst.clear();
                break;
        }
        cout << endl;
    }
}

void RBTTestCase()
{
    MyRedBlackTree<int> rbt;
    
    int key;
    int value;
    while (true)
    {
        cout << "1. insert(int value)" << endl;
        cout << "2. erase(int value)" << endl;
        cout << "3. print" << endl;
        cout << "4. size()" << endl;
        cout << "5. end" << endl;
        cout << "키를 입력하세요 : ";
        cin >> key;

        switch (key)
        {
            case 1:
                cout << "삽입할 값을 입력하세요 : ";
                cin >> value;
                rbt.insert(value);
                break;
            case 2:
                cout << "삭제할 값을 입력하세요 : ";
                cin >> value;
                rbt.erase(value);
                break;
            case 3:
                rbt.print();
                break;
            case 4:
                cout << "size() = " << rbt.size() << endl;
                break;
        }
       
        if (key > 4)
            break;
    }
}

void HTTestCase()
{
    MyHeapTree<int> ht;

    int key;
    int val = 0;
    int type;

    while (true)
    {
        cout << "1 : insert(value)" << endl;
        cout << "2 : eraseRoot()" << endl;
        cout << "3 : print()" << endl;
        cout << "4 : size()" << endl;
        cout << "5 : setHeapType" << endl;
        cout << "6 : end" << endl;
        cout << "key를 입력하세요 : ";
        cin >> key;
        cout << endl;

        switch (key)
        {
            case 1:
                while (true)
                {
                    cout << "삽입 할 값을 입력하세요 (9999입력시 종료) : ";
                    cin >> val;
                    if (val == 9999)
                        break;
                    ht.insert(val);
                }
                break;
            case 2:
                ht.eraseRoot();
                break;
            case 3:
                ht.printTree();
                break;
            case 4:
                cout << "size = " << ht.size() << endl;
                break;
            case 5:
                cout << "Heap Type 변경은 tree가 비어있어야 합니다(그렇지 않으면 assert...)" << endl;
                cout << "1. MaxHeap" << endl << "2. MinHeap" << endl << "3. 돌아가기" << endl;
                cout << "Heap Type을 골라주세요 : " << endl;
                cin >> type;
                if (type == 1)
                    ht.setHeapType(HeapType::MaxHeap);
                else if (type == 2)
                    ht.setHeapType(HeapType::MinHeap);
                break;
            case 6:
                break;
        }
        cout << endl;
    }
}
