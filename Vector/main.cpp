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

using namespace std;

int main(int argc, const char* argv[])
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
            default:
                return 0;
        }
    }
}

//int main(int argc, const char* argv[])
//{
//    MyCompleteBinaryTree<int> cbt;
//    MyBinarySearchTree<int> bst;
//    int tree;
//    int key;
//    int data;
//    int index;
//    int order;
//
//    cout << "1. 완전 이진 트리" << endl;
//    cout << "2. 이진 탐색 트리" << endl;
//    cout << "키를 입력하세요 : ";
//    cin >> tree;
//    cout << endl;
//
//    if(tree == 1)
//    {
//        while(true)
//        {
//            cout << "1. push_back(value)" << endl;
//            cout << "2. pop_back()" << endl;
//            cout << "3. insert(index, value)" << endl;
//            cout << "4. erase(index)" << endl;
//            cout << "5. 순회출력" << endl;
//            cout << "6. 트리형태 출력" << endl;
//            cout << "7. size()" << endl;
//            cout << "8. clear()" << endl;
//            cout << "9. 종료" << endl;
//
//            cout << "키를 입력하세요 : ";
//            cin >> key;
//            cout << endl;
//
//            if (key > 8)
//                break;
//
//            switch(key)
//            {
//                case 1:
//                    cout << "insert 할 값을 입력하세요 : ";
//                    cin >> data;
//                    cbt.push_back(data);
//                    break;
//                case 2:
//                    cbt.pop_back();
//                    break;
//                case 3:
//                    cout << "insert할 값을 입력해주세요 : ";
//                    cin >> data;
//                    cout << "insert할 위치를 입력하세요 (root = 0) : ";
//                    cin >> index;
//                    cbt.insert(index, data);
//                    break;
//                case 4:
//                    cout << "erase 할 위치를 입력하세요 (root = 0) : ";
//                    cin >> index;
//                    cbt.erase(index);
//                    break;
//                case 5:
//                    cout << "1.전위순회" << endl;
//                    cout << "2.중위순회" << endl;
//                    cout << "3.후위순회" << endl;
//                    cout << "순회 방식을 선택해주세요 : ";
//                    cin >> order;
//                    if(order == 1)
//                        cbt.setTraversalOrder(cbt.PREORDER);
//                    else if (order == 2)
//                        cbt.setTraversalOrder(cbt.INORDER);
//                    else
//                        cbt.setTraversalOrder(cbt.POSTORDER);
//
//                    cbt.printWithTraversalOrder();
//                    break;
//                case 6:
//                    cbt.printTree();
//                    break;
//                case 7:
//                    cout << "size = " << cbt.size() << endl;
//                    break;
//                case 8:
//                    cbt.clear();
//                    break;
//            }
//            cout << endl;
//        }
//    }
//    else if (tree == 2)
//    {
//        while(true)
//        {
//            cout << "1. insert(value)" << endl;
//            cout << "2. erase(value)" << endl;
//            cout << "3. 트리형태 출력" << endl;
//            cout << "4. size() " << endl;
//            cout << "5. clear() " << endl;
//            cout << "6. 종료" << endl;
//
//            cout << "키를 입력하세요 : ";
//            cin >> key;
//            cout << endl;
//            if (key > 5)
//                break;
//
//            switch(key)
//            {
//                case 1:
//                    cout << "insert할 값을 입력하세요 : ";
//                    cin >> data;
//                    bst.insert(data);
//                    break;
//                case 2:
//                    cout << "erase할 값을 입력하세요 : ";
//                    cin >> data;
//                    bst.erase(data);
//                    break;
//                case 3:
//                    bst.print();
//                    break;
//                case 4:
//                    cout << "size = " << bst.size() << endl;
//                    break;
//                case 5:
//                    bst.clear();
//                    break;
//            }
//            cout << endl;
//        }
//    }
//}
