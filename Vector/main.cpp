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

using namespace std;

int main(int argc, const char* argv[])
{
    MyBinarySearchTree<int> test;
    
//    test.insert(5);
//    test.insert(3);
//    test.insert(4);
//    test.insert(2);
//    test.insert(1);
    
    test.erase(2);
    
    
//    MyCompleteBinaryTree<int> test;
//
//    for(int i = 1; i < 30; i++)
//    {
//        test.push_back(i);
//    }
//
//    test.printTree();
//
//    test.erase(2);
//
//    cout << endl;
//    test.printTree();
//
//    test.setTraversalOrder(test.PREORDER);
//    test.printWithTraversalOrder();
//
//    test.setTraversalOrder(test.INORDER);
//    test.printWithTraversalOrder();
//
//    test.setTraversalOrder(test.POSTORDER);
//    test.printWithTraversalOrder();
//
//    test.clear();
//
//    cout << test.size() << endl;
}
