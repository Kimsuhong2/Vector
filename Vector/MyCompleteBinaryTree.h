#pragma once
#include <iostream>

template <typename T>
class MyCompleteBinaryTree
{
private:
    Node<T>* rootNode;
    size_t treeSize;
    
public:
    MyCompleteBinaryTree(T val) : rootNode(new Node<T>(val)), treeSize(1) {}
    MyCompleteBinaryTree(Node<T>* newNode = nullptr) : rootNode(newNode)
    {
        if (newNode == nullptr)
        {
            treeSize = 0;
        }
        else
        {
            treeSize = 1;
        }
    }
    
public:
    size_t size()
    {
        return treeSize;
    }
    
    bool empty()
    {
        return treeSize == 0;
    }
    
    void insert(T val)
    {
        
    }
};
