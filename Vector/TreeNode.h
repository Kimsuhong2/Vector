#pragma once
#include <iostream>

template <typename T>
class TreeNode
{
public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
    
public:
    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}

    ~TreeNode()
    {
        if(left != nullptr)
        {
            delete left;
        }
        
        if(right!=nullptr)
        {
            delete right;
        }
    }
};
