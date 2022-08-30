#pragma once
#include <iostream>
#include "MyCompleteBinaryTree.h"


enum TraversalOrder {PREORDER, INORDER, POSTORDER};
enum HeapType {MaxHeap, MinHeap};

template <typename T>
class MyHeapTree
{
public:
    
private:
    MyVector<TreeNode<T>*> tree;
    size_t treeSize;
    TraversalOrder order;
    HeapType type;
    
public:
    MyHeapTree()
    : treeSize(0), order(TraversalOrder::PREORDER), type(HeapType::MinHeap){}
    ~MyHeapTree(){}
    
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
    
    /**
     Tree형태로 출력해주는 함수
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
    
    /**
     제일 마지막 노드에 값을 넣어준 뒤, maxheap, minheap에 맞게 재배치.
     case Maxheap :
        maxHeap에서 부모는 자기 자식보다 항상 값이 커야 함.
        그렇기 때문에 newNode의 값이 parentNode의 값보다 크면 swap(newNode, parentNode).
        부모의 위치로 간 newNode가 새로운 부모의 값보다 클 수 있으니 반복문을 통해 root에 도달할 때 까지 반복.
     case MinHeap :
        MinHeap에서 부모는 자기 자식보다 항상 값이 작아야 함.
        반복문을 통해 newNode의 값이 부모의 값보다 작을때까지 반복.
     */
    void insertRebuild(size_t index)
    {
        while (index != 0)
        {
            size_t parentIndex = (index - 1) / 2;
            switch (type)
            {
                case HeapType::MaxHeap:
                    if (tree[index]->data > tree[parentIndex]->data)
                        swap(tree[index]->data, tree[parentIndex]->data);
                    else
                        return;
                    break;
                    
                case HeapType::MinHeap:
                    if (tree[index]->data < tree[parentIndex]->data)
                        swap(tree[index]->data, tree[parentIndex]->data);
                    else
                        return;
                    break;
            }
            
            index = parentIndex;
        }
    }
    
    /**
     root노드를 삭제하고 제일 마지막에 들어온 node가 root로 옮겨진 후 기준에 맞게 newRoot를 이동시켜 줘야 함.
     case MaxHeap :
         MaxHeap은 부모의 값이 항상 자식보다 커야 함.
         그렇기 때문에 자기 자신보다 값이 큰 child와 값을 바꿔줘야 함.
         자식이 2개가 모두 자기 자신보다 값이 큰 경우 우선순위가 높은 자식과 바꿔줌 ( 우선순위 → 두 자식중 값이 더 큰 놈)
         반복문을 통해 자식이 없을 때까지 반복.
     case MinHeap:
         MinHeap은 부모의 값이 항상 자식보다 작아야 함.
         그렇기 때문에 자기 자신보다 값이 작은 child와 값을 바꿔줘야 함.
         자식이 2개가 모두 자기 자신보다 값이 작은 경우 우선순위가 높은 자식과 바꿔줌 ( 우선순위 → 두 자식중 값이 더 작은 놈)
         반복문을 통해 자식이 없을때까지 반복.
     */
    void eraseReBuild()
    {
        size_t currentIndex = 0;
        
        while ((currentIndex * 2 + 1) < (treeSize - 1))
        {
            size_t priorChildIndex = getPriorChildIndex(currentIndex);
            
            switch (type)
            {
                case HeapType::MaxHeap:
                    // 우선순위가 높은 자식노드와 값을 비교해서, 자식의 값이 자신의 값보다 크면 swap;
                    if (tree[currentIndex]->data < tree[priorChildIndex]->data)
                        swap(tree[currentIndex]->data, tree[priorChildIndex]->data);
                    else
                        return;
                    
                    break;
                    
                case HeapType::MinHeap:
                    // 우선순위가 높은 자식노드와 값을 비교해서, 자식의 값이 자신의 값보다 작으면 swap;
                    if (tree[currentIndex]->data > tree[priorChildIndex]->data)
                        swap(tree[currentIndex]->data, tree[priorChildIndex]->data);
                    else
                        return;
                    
                    break;
            }
            currentIndex = priorChildIndex;
        }
    }
    
    /**
     Heap Tree는 이진 트리 기반으로 만들어짐.
     그렇기 때문에 부모의 index로 자식의 index를 구할 수 있음.
                    0
                1               2
              3        4     5       6
    왼쪽 자식    index  ==  부모 index * 2 + 1
    오른쪽 자식 index  ==  부모 index * 2 + 2
    0의 왼쪽 자식은    1,   0 * 2 + 1 = 1    (O)
    0의 오른쪽 자식은 2,   0 * 2 + 2 = 2    (O)
    2의 왼쪽 자식은    5,   2 * 2 + 1 = 5    (O)
    2의 오른쪽 자식은 6,   2 * 2 + 2 = 6    (O)
     */
    /**
     우선순위가 더 높은 자식의 인덱스를 반환.
     */
    size_t getPriorChildIndex(size_t parentIndex)
    {
        size_t leftChildIndex = parentIndex * 2 + 1;
        size_t rightChildIndex = parentIndex * 2 + 2;
        
        switch (type)
        {
            case HeapType::MaxHeap:
                if (tree[rightChildIndex] == nullptr || tree[leftChildIndex]->data > tree[rightChildIndex]->data)
                    return leftChildIndex;
                else
                    return rightChildIndex;
                break;
                
            case HeapType::MinHeap:
                if (tree[leftChildIndex] == nullptr || tree[leftChildIndex]->data < tree[rightChildIndex]->data)
                    return leftChildIndex;
                else
                    return rightChildIndex;
                break;
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
        for(size_t i = treeSize-1; i >= 0; --i)
        {
            delete tree[i];
            tree.pop_back();
        }
        
        treeSize = 0;
    }
    
    /**
        제일 마지막 위치에 새로운 노드를 삽입해 주고,
        insertRebuild를 통해 재배치.
     */
    void insert(T val)
    {
        TreeNode<T>* newNode = new TreeNode<T>(val);
        
        tree.push_back(newNode);
      
        linkWithParentNode(tree[treeSize], treeSize);
        
        insertRebuild(treeSize);
        
        ++treeSize;
    }
    
    /**
     HeapTree에서의 삭제는 항상 루트노드를 삭제함.
     MaxHeap은 최대값 (루트노드가 항상 최대값)
     MinHeap은 최소값 (루트노드가 항상 최소값)
     
     루트노드를 삭제 후 제일 마지막에 들어온 node를 root에 올리고,
     해당 노드를 알맞는 자리에 이동시킴.
     */
    void eraseRoot()
    {
        if (treeSize == 0)
            return;
    
        --treeSize;
        
        swap(tree[0]->data, tree[treeSize]->data);
        linkWithParentNode(nullptr, treeSize);
        delete tree[treeSize];
        eraseReBuild();
    }
    
    /**
     MaxHeap, MinHeap을 설정해주는 함수.
        tree가 비어있을때만 값을 바꿀 수 있음.
     */
    void setHeapType(HeapType type)
    {
        assert(treeSize == 0);
        
        this->type = type;
    }
    
    /**
     traversal order를 설정해줌
     */
    void setTraversalOrder(TraversalOrder order)
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
                default:
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
};
