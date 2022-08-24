#pragma once
#incldue <iostream>
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
        delete left;
        delete right;
    }
}
