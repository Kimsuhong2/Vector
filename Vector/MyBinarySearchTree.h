#pragma once
#include <iostream>

template <typename T>
class MyBinarySearchTree
{
private:
    TreeNode<T>* root;
    size_t treeSize;
    
public:
    MyBinarySearchTree() : root(nullptr), treeSize(0) {};
    ~MyBinarySearchTree() {}
    
public:
    size_t size()
    {
        return treeSize;
    }
    
    bool empty()
    {
        return treeSize == 0;
    }
    
    bool insert(T val)
    {
        
        TreeNode<T>* newNode = new TreeNode<T>(val);
        
        if (treeSize == 0)
        {
            root = newNode;
            ++treeSize;
            
            return true;
        }
        
        TreeNode<T>* currentNode = root;
        while(currentNode != nullptr)
        {
            if (val == currentNode->data)
            {
                return false;
            }
            else if (val > currentNode->data)
            {
                if (currentNode->right == nullptr)
                {
                    currentNode->right = newNode;
                    ++treeSize;
                    return true;
                }
                else
                {
                    currentNode = currentNode->right;
                }
            }
            else
            {
                if (currentNode->left == nullptr)
                {
                    currentNode->left = newNode;
                    ++treeSize;
                    return true;
                }
                else
                {
                    currentNode = currentNode->left;
                }
            }
        }
        
        return false;
    }
    
    TreeNode<T>* search(TreeNode<T>* currentNode, T val)
    {
        if (currentNode == nullptr || currentNode->data == val)
            return currentNode;
        
        if (currentNode->data > val)
            return search(currentNode->left, val);
        else
            return search(currentNode->right, val);
    }
    
    TreeNode<T>* findMinNode(TreeNode<T>* subTreeRoot)
    {
        while (subTreeRoot->left != nullptr)
            subTreeRoot = subTreeRoot->left;
        
        return subTreeRoot;
    }
    
    bool erase(T val)
    {
        TreeNode<T>* parentNode = root;
        TreeNode<T>* tempNode;
        while (parentNode!=nullptr)
        {
            if (parentNode->data > val)
                tempNode = parentNode->left;
            else if (parentNode->data < val)
                tempNode = parentNode->right;

            if (tempNode->data != val)
            {
                parentNode = tempNode;
            }
            else
            {
                if (parentNode->left->data == val)
                {
                    if (tempNode->left == nullptr)
                    {
                        parentNode->left = tempNode->right;
                        tempNode->left = nullptr;
                        tempNode->right = nullptr;
                        delete tempNode;
                    }
                    else if (tempNode->right == nullptr)
                    {
                        parentNode->left = tempNode->left;
                        tempNode->left = nullptr;
                        tempNode->right = nullptr;
                        delete tempNode;
                    }
                    else
                    {
                        
                    }
                    
                    --treeSize;
                    return true;
                }
                else
                {
                    if (tempNode->left == nullptr)
                    {
                        parentNode->right = tempNode->right;
                        tempNode->left = nullptr;
                        tempNode->right = nullptr;
                        delete tempNode;
                    }
                    else if (tempNode->right == nullptr)
                    {
                        parentNode->right = tempNode->left;
                        tempNode->left = nullptr;
                        tempNode->right = nullptr;
                        delete tempNode;
                    }
                    else
                    {
                        
                    }
                    
                    --treeSize;
                    return true;
                }
            }
        }
        
        return false;
    }
};
