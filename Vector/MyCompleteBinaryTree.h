#pragma once
#include <iostream>
#include <queue>
#include "MyVector.h"
#include "TreeNode.h"

using namespace std;

template <typename T>
class MyCompleteBinaryTree
{
public:
    enum traversalOrder {PREORDER, INORDER, POSTORDER};
private:
    MyVector<TreeNode<T>*> tree;
    size_t treeSize;
    traversalOrder order = PREORDER;
    
public:
    MyCompleteBinaryTree() : treeSize(0){}
    ~MyCompleteBinaryTree(){}
    
private:
    
    /**
    child node와, child node의 index를 받아, 부모의 자식으로 연결시켜 줌.
     */
    void linkWithParentNode(TreeNode<T>* childNode, size_t childIndex)
    {
        if(childIndex == 0)
            return;
        
        size_t parentIndex = (childIndex - 1) / 2;
        
        if (childIndex % 2 == 0)
            tree[parentIndex]->right = childNode;
        else
            tree[parentIndex]->left = childNode;
    }
    
    /**
        전위 순회 ( Preorder Traversal)
        1. 자기 자신을 처리함.
        2. 왼쪽 자식을 방문함.
        3. 오른쪽 자식을 방문함.
     */
    void preOrder(TreeNode<T>* node)
    {
        if (node == nullptr)
            return;
        
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
    
    /**
        중위 순회 ( Preorder Traversal)
        1. 왼쪽 자식을 방문함.
        2. 자기 자신을 처리함.
        3. 오른쪽 자식을 방문함.
     */
    void inOrder(TreeNode<T>* node)
    {
        if (node != nullptr)
        {
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }
    }
    
    /**
        후위 순회 ( Preorder Traversal)
        1. 왼쪽 자식을 방문함.
        2. 오른쪽 자식을 방문함.
        3. 자기 자신을 처리함.
     */
    void postOrder(TreeNode<T>* node)
    {
        if (node != nullptr)
        {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->data << " ";
        }
    }
    
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
        delete tree[0];
        
        treeSize = 0;
    }
    
    /**
     complete binary tree는 이진 트리 이면서 왼쪽 노드들 부터 채워져야 됨.
     그렇기 때문에 자식의 index로 부모의 index를 구할 수 있음.
                    0
                1               2
              3        4     5       6
    부모 index  ==  (자식 index - 1)  /  2
    1의 부모는 0,   (1 - 1)  /  2  =  0    (O)
    2의 부모는 0,   (2 - 1)  /  2  =  0    (O)
    5의 부모는 2,   (5 - 1)  /  2  =  2    (O)
    또한 인덱스가 홀수인 노드는 부모의 왼쪽에, 인덱스가 짝수인 노드는 부모의 오른쪽에 위치함.
     */
    void push_back(T val)
    {
        TreeNode<T>* newNode = new TreeNode<T>(val);
        
        tree.push_back(newNode);
      
        linkWithParentNode(tree[treeSize], treeSize);
        
        ++treeSize;
    }
    
    /**
     가장 늦게 들어온 node를 제거하고,
     해당 노드를 자식으로 둔 부모 노드를 찾아가 참조 해제 시켜 줌.
     */
    void pop_back()
    {
        if (treeSize <= 0)
        {
            return;
        }
        
        TreeNode<T>* treeNode = tree.back();
        tree.pop_back();
        delete treeNode;
        
        --treeSize;
        linkWithParentNode(nullptr, treeSize);
    }
    
    /**
     vector의 insert를 통해 원하는 위치에 값을 넣어주고
     해당 위치부터 마지막 위치까지의 노드들을 새로 배치함.
     */
    void insert(int index, T val)
    {
        if (index >= treeSize)
        {
            push_back(val);
            return;
        }
        
        typename MyVector<TreeNode<T>*>::iterator iter = tree.begin() + index;
        
        tree.insert(iter, new TreeNode(val));
        
        ++treeSize;
        
        for(int i = index; i < treeSize; i++)
        {
            tree[i]->left = nullptr;
            tree[i]->right = nullptr;
            linkWithParentNode(tree[i], i);
        }
    }
    
    void erase(int index)
    {
        assert(treeSize > 0);
        
        TreeNode<T>* targetNode = tree[index];
        
        typename MyVector<TreeNode<T>*>::iterator iter = tree.begin() + index;
        tree.erase(iter);
        
        --treeSize;
        
        for(int i = index; i < treeSize; i++)
        {
            tree[i]->left = tree[i]->right = nullptr;
            linkWithParentNode(tree[i], i);
        }
        
        targetNode->left = targetNode->right = nullptr;
        delete targetNode;
    }
    
    /**
     traversal order를 설정해줌
     */
    void setTraversalOrder(traversalOrder order)
    {
        this->order = order;
    }
    
    /**
    현재 설정되어있는 traversal order로 순회하면서 node의 값을 출력해 줌.
     */
    void printWithTraversalOrder()
    {
        if (treeSize != 0)
        {
            switch (order)
            {
                case PREORDER:
                    preOrder(tree.front());
                    break;
                case INORDER:
                    inOrder(tree.front());
                    break;
                case POSTORDER:
                    postOrder(tree.front());
                    break;
            }
        }
        cout << endl;
    }
    
    void printTree()
    {
        if (treeSize != 0)
            treeOrder(tree.front(), 0);
        cout << endl;
    }
 
    void insert2(T val)
    {
        if (treeSize == 0)
        {
            push_back(val);
            return;
        }
        
        queue<TreeNode<T>*> q;
        q.push(tree[0]);
        TreeNode<T>* newNode = new TreeNode<T>(val);
        
        while (!q.empty())
        {
            TreeNode<T>* temp;
            temp = q.front();
            q.pop();
            
            if (temp->left == nullptr)
            {
                temp->left = newNode;
                break;
            }
            else if (temp->right == nullptr)
            {
                temp->right = newNode;
                break;
            }
            
            q.push(temp->left);
            q.push(temp->right);
        }
        
        ++treeSize;
    }
};




/**
 insert by bfs
 */
//void insert(T val)
//{
//    if (treeSize == 0)
//    {
//        push_back(val);
//        return;
//    }
//
//    queue<TreeNode<T>**> q;
//    q.push(&tree[0]);
//    TreeNode<T>* newNode = new TreeNode<T>(val);
//
//    while(!q.empty())
//    {
//        TreeNode<T>** temp;
//        temp = q.front();
//        q.pop();
//
//        if((*temp)->left != nullptr)
//        {
//            q.push(&(*temp)->left);
//        }
//        else
//        {
//            (*temp)->left = newNode;
//            ++treeSize;
//            break;
//        }
//
//        if((*temp)->right != nullptr)
//        {
//            q.push(&(*temp)->right);
//        }
//        else
//        {
//            (*temp)->right = newNode;
//            ++treeSize;
//            break;
//        }
//    }
//}
