#pragma once
#include <iostream>

enum COLOR {RED, BLACK};

template <typename T>
class TreeNode
{
public:
    T data;
    TreeNode<T>* parent;
    TreeNode<T>* left;
    TreeNode<T>* right;
    COLOR color;
    
public:
    TreeNode(T val) : data(val), parent(nullptr), left(nullptr), right(nullptr), color(COLOR::RED) {}

    ~TreeNode()
    {
        left = right = nullptr;
        delete left;
        delete right;
    }
};
