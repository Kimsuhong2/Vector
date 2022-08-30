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
    ~MyBinarySearchTree()
    {
        delete root;
    }
    
private:
    /**
     재귀를 활용해 해당 노드가 있는지 찾아 줌.
     */
    TreeNode<T>* searchNode(TreeNode<T>* currentNode, T val)
    {
        if (currentNode == nullptr || currentNode->data == val)
            return currentNode;
        
        if (currentNode->data > val)
            return searchNode(currentNode->left, val);
        else
            return searchNode(currentNode->right, val);
    }
    
    /**
     재귀를 활용해 삭제하고자 하는 노드를 찾아서 삭제해줌.
     삭제에는 3가지 경우의 수가 있음
        1. 삭제한 노드가 자식노드를 갖고있지 않을 때.    ( no child )
            ㄴ 해당 노드를 삭제해주면 됨.
        2. 삭제한 노드가 1개의 자식노드를 갖고 있을 때. ( left or right )
            ㄴ 삭제한 노드에 자식노드를 위치시킴.
        3. 삭제한 노드가 2개의 자식노드를 갖고 있을 때. ( left and right )
            ㄴ 삭제한 노드의 오른쪽 subtree에서 제일 작은 값을 삭제한 노드에 위치시킴.  ←적용
            ㄴ 삭제한 노드의 왼쪽 subtree에서 제일 큰 값을 삭제한 노드에 위치시킴.
     */
    TreeNode<T>* eraseNode(TreeNode<T>* rootNode, T val)
    {
        if (rootNode == nullptr)
            return rootNode;
        
        if (rootNode->data > val)
        {
            rootNode->left = eraseNode(rootNode->left, val);
        }
        else if (rootNode->data < val)
        {
            rootNode->right = eraseNode(rootNode->right, val);
        }
        else
        {
            if (rootNode->left == nullptr)
            {
                TreeNode<T>* temp = rootNode;
                rootNode = temp->right;
                delete temp;
            }
            else if (rootNode->right == nullptr)
            {
                TreeNode<T>* temp = rootNode;
                rootNode = temp->left;
                delete temp;
            }
            else
            {
                TreeNode<T>* minNode = findMinNode(rootNode->right);
                rootNode->data = minNode->data;
                rootNode->right = eraseNode(rootNode->right, minNode->data);
                return rootNode;
            }
            
            --treeSize;
        }
        return rootNode;
    }
    
    /**
     인자로 넘겨받은 subTreeRoot에서 가장 작은 값을 가진 Node를 찾아서 넘겨 줌.
    */
    TreeNode<T>* findMinNode(TreeNode<T>* subTreeRoot)
    {
        while (subTreeRoot->left != nullptr)
            subTreeRoot = subTreeRoot->left;
        
        return subTreeRoot;
    }
    
    /**
     트리 모양으로 출력해줌.
     */
    void treeOrder(TreeNode<T>* node, int depth = 0)
    {
        if (node != nullptr)
        {
            treeOrder(node->right, depth + 1);
            for(int i = 0 ; i < depth; ++i)
            {
                cout << "  ";
            }
            cout << node->data << endl;
            treeOrder(node->left, depth + 1);
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
    
    void clear()
    {
        queue<TreeNode<T>*> q;
        q.push(root);
        
        while(!q.empty())
        {
            TreeNode<T>** temp = &q.front();
            q.pop();
            
            if((*temp)->left != nullptr)
                q.push((*temp)->left);
            
            if((*temp)->right != nullptr)
                q.push((*temp)->right);
            
            delete *temp;
        }
        root = nullptr;
        treeSize = 0;
    }
    
    /**
    반복문을 통해서 newNode가 들어가야 될 위치를 찾아서 넣어줌.
     */
    bool insert(T val)
    {
        TreeNode<T>* newNode = new TreeNode<T>(val);
        TreeNode<T>* currentNode = root;
        
        if (currentNode == nullptr)
        {
            root = newNode;
            ++treeSize;
            return true;
        }
        
        while (currentNode != nullptr)
        {
            if (currentNode->data == val)
                return false;
            
            if (currentNode->data > val)
            {
                if (currentNode->left == nullptr)
                {
                    currentNode->left = newNode;
                    break;
                }
                else
                {
                    currentNode = currentNode->left;
                    
                }
            }
            else
            {
                if (currentNode->right == nullptr)
                {
                    currentNode->right = newNode;
                    break;
                }
                else
                {
                    currentNode = currentNode->right;
                }
            }
        }
        
        ++treeSize;
        return true;
        
//        TreeNode<T>* newNode = new TreeNode<T>(val);
//        TreeNode<T>** currentNode = &root;
//
//        while(*currentNode != nullptr)
//        {
//            if (val == (*currentNode)->data)
//            {
//                return false;
//            }
//            else if (val > (*currentNode)->data)
//            {
//                currentNode = &((*currentNode)->right);
//            }
//            else
//            {
//                currentNode = &((*currentNode)->left);
//            }
//        }
//
//        *currentNode = newNode;
//        ++treeSize;
//        return true;
    }
    
    bool search(T val)
    {
        return searchNode(root, val) != nullptr;
    }
    
    bool erase(T val)
    {
        size_t prevSize = treeSize;
        
        root = eraseNode(root, val);
        
        return prevSize != treeSize;
    }
    
    void print()
    {
        treeOrder(root);
    }
};
