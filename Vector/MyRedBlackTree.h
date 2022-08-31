#pragma once
#include <iostream>
#include "TreeNode.h"

/**
 Red - Black Tree ( 자가 균형 이진 탐색 트리 )
 
 1. Root Property      :  루트노드의 색깔은 항상 검정(black)이다.
 2. External Property :  모든 리프(NIL)들은 검정(black)이다.
 3. Internal Property  :  빨강노드의 자식은 검정이다 == 빨강색 노드가 연속으로 나올 수 없다.
 4. Depth Property    :  모든 리프노드에서 Black Depth는 같다. == 리프노드에서 루트노드까지 가는 경로에서 만나는 블랙노드의 개수는 같다.
 */
template <typename T>
class MyRedBlackTree
{
private:
    TreeNode<T>* root;
    TreeNode<T>* nilNode;
    size_t treeSize;
    
public:
    MyRedBlackTree() : root(nullptr), nilNode(new TreeNode<T>(0)), treeSize(0)
    {
        nilNode->color = COLOR::BLACK;
    }
    ~MyRedBlackTree()
    {
        delete root;
        delete nilNode;
    }
    
private:
    /**
        parent대신 child를 조부모와 연결시켜주는 함수.
        parent가 grandparent의 왼쪽자식일 경우, grandparent의 왼쪽자식으로 child를 연결.
        parent가 grandparent의 오른쪽 자식일 경우, grandparent의 오른쪽 자식으로 child를 연결.
        child의 부모로 grandparent지정.
     */
    void transPlant(TreeNode<T>* parent, TreeNode<T>* child)
    {
        TreeNode<T>* grandparent = parent->parent;
        
        if (grandparent == nilNode)
        {
            root = child;
        }
        else if (parent == grandparent->left)
        {
            grandparent->left = child;
        }
        else
        {
            grandparent->right = child;
        }

        child->parent = grandparent;
    }
    
    /**
     인자로 넘겨받은 subTreeRoot에서 가장 작은 값을 가진 Node를 찾아서 넘겨 줌.
    */
    TreeNode<T>* findMinNode(TreeNode<T>* subTreeRoot)
    {
        while (subTreeRoot->left != nilNode)
            subTreeRoot = subTreeRoot->left;
        
        return subTreeRoot;
    }
    
    /**
     트리 모양으로 출력해줌.
     */
    void treeOrder(TreeNode<T>* node, int depth = 0)
    {
        if (node != nilNode && node != nullptr)
        {
            treeOrder(node->right, depth + 1);
            for (int i = 0 ; i < depth; ++i)
            {
                cout << "  ";
            }
            if (node->color == COLOR::RED)
                cout << "R";
            else
                cout << "B";
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
    
    void print()
    {
        treeOrder(root);
    }
    
    /**
     node를 기준으로 왼쪽으로 회전시켜주는 함수.
     */
    void leftRotate(TreeNode<T>* node)
    {
        TreeNode<T>* rightChild = node->right;
        node->right = rightChild->left;
        
        if (rightChild->left != nilNode)
        {
            node->right->parent = node;
        }
        
        rightChild->parent = node->parent;
        
        if (rightChild->parent == nilNode)
        {
            root = rightChild;
        }
        else if (node == node->parent->left)
        {
            rightChild->parent->left = rightChild;
        }
        else
        {
            rightChild->parent->right = rightChild;
        }
        
        node->parent = rightChild;
        rightChild->left = node;
    }
    
    /**
     node를 기준으로 오른쪽 회전 시켜주는 함수.
     */
    void rightRotate(TreeNode<T>* node)
    {
        TreeNode<T>* leftChild = node->left;
        node->left = leftChild->right;
        
        if (leftChild->left != nilNode)
        {
            node->left->parent = node;
        }
        
        leftChild->parent = node->parent;
        
        if (leftChild->parent == nilNode)
        {
            root = leftChild;
        }
        else if (node == node->parent->left)
        {
            leftChild->parent->left = leftChild;
        }
        else
        {
            leftChild->parent->right = leftChild;
        }
        
        node->parent = leftChild;
        leftChild->right = node;
    }
    
    /**
     반복문을 통해서 삽입 될 위치를 찾고, 해당 위치에 newNode를 추가.
     */
    bool insert(T val)
    {
        TreeNode<T>* newNode = new TreeNode<T>(val);
        newNode->left = nilNode;
        newNode->right = nilNode;
        
        TreeNode<T>* currentNode = root;
        
        /**
         treesize == 0 이면 root노드에 새로운 노드를 추가.
         */
        if (treeSize == 0)
        {
            root = newNode;
            root->parent = nilNode;
        }
        else
        {
            while (currentNode != nilNode)
            {
                if (currentNode->data == val)
                    return false;
                
                if (currentNode->data > val)
                {
                    if (currentNode->left == nilNode)
                    {
                        currentNode->left = newNode;
                        newNode->parent = currentNode;
                        break;
                    }
                    else
                    {
                        currentNode = currentNode->left;
                    }
                }
                else
                {
                    if (currentNode->right == nilNode)
                    {
                        currentNode->right = newNode;
                        newNode->parent = currentNode;
                        break;
                    }
                    else
                    {
                        currentNode = currentNode->right;
                    }
                }
            }
        }
        
        insertFixUp(newNode);
        ++treeSize;
        return true;
    }
    
    /**
     삽입 과정에서 3가지 상황이 발생할 수 있음.
     case 1. newNode의 삼촌 노드가 빨강색인 경우.
     case 2. newNode의 삼촌 노드가 검정색인 경우. (newNode가 부모의 오른쪽 자식인 경우)
     case 3. newNode의 삼촌 노드가 검정색인 경우. (newNode가 부모의 왼쪽 자식인 경우)
     */
    void insertFixUp(TreeNode<T>* node)
    {
        while (node != root && node->parent->color == COLOR::RED)
        {
            TreeNode<T>* grandparent = node->parent->parent;
            bool isLeftChild = node->parent == grandparent->left;
            TreeNode<T>* uncle = isLeftChild ? grandparent->right : grandparent->left;
            
            /**
            case 1:
                step 1. 부모의 색깔을 검정색으로 바꾼다.
                step 2. 삼촌의 색깔을 검정색으로 바꾼다.
                step 3. 조부모의 색깔을 빨강색으로 바꾼다.
            이렇게 할 경우 새로 삽입한 노드는 해결 됐을지 몰라도 조부모에서 red-red충돌이 발생할 수 있기 때문에
            반복문을 통해 root노드가 나올때까지 같은 방법으로 해결을 해준다.
             */
            if (uncle != nullptr && uncle->color == COLOR::RED)
            {
                node->parent->color = COLOR::BLACK;
                uncle->color = COLOR::BLACK;
                grandparent->color = COLOR::RED;
                node = grandparent;
            }
            else
            {
                /**
                 case 2.
                    step 1. 삽입한 노드, 부모 노드, 조부모 노드를 오름차순으로 정렬.
                     
                    ↑ case 3로 바꿔주는 과정
                 */
                if (node == (isLeftChild ? node->parent->right : node->parent->left))
                {
                    node = node->parent;
                    isLeftChild ? leftRotate(node) : rightRotate(node);
                }
                
                /**
                 case 3.
                    step 1. 오름차순 결과에서 가운데 있는 노드를 부모노드, 나머지를 자식노드로 지정 (leftRotate, rightRotate)
                    step 2. 새로운 부모를 검정색으로, 자식노드들은 빨강색으로 지정.
                 */
                node->parent->color = COLOR::BLACK;
                grandparent->color = COLOR::RED;
                
                isLeftChild ? rightRotate(grandparent) : leftRotate(grandparent);
            }
        }
        
        root->color = COLOR::BLACK;
    }
    
    /**
     반복문을 통해서 삭제 할 node를 찾아서 삭제해준다.
     삭제에는 3가지 경우의 수가 있음
        1. 삭제한 노드가 자식노드를 갖고있지 않을 때.    ( no child )
            ㄴ 해당 노드를 삭제해주면 됨.
        2. 삭제한 노드가 1개의 자식노드를 갖고 있을 때. ( left or right )
            ㄴ 삭제한 노드의 위치에 자식노드를 위치시킴.
        3. 삭제한 노드가 2개의 자식노드를 갖고 있을 때. ( left and right )
            ㄴ 삭제한 노드의 오른쪽 subtree에서 제일 작은 값을 삭제한 노드에 위치시킴.  ←적용
            ㄴ 삭제한 노드의 왼쪽 subtree에서 제일 큰 값을 삭제한 노드에 위치시킴.
     */
    bool erase(T val)
    {
        if (root == nullptr)
        {
            return false;
        }
        
        TreeNode<T>* currentNode = root;
        TreeNode<T>* newChild;
        
        while (currentNode != nilNode)
        {
            if (currentNode->data < val)
            {
                currentNode = currentNode->right;
            }
            else if (currentNode->data > val)
            {
                currentNode = currentNode->left;
            }
            else
            {
                COLOR orignalColor = currentNode->color;
                /**
                 삭제될 노드의 자식이 1개 이하일 때
                 */
                if (currentNode->left == nilNode)
                {
                    newChild = currentNode->right;
                    transPlant(currentNode, newChild);
                }
                else if (currentNode->right == nilNode)
                {
                    newChild = currentNode->left;
                    transPlant(currentNode, newChild);
                }
                /**
                삭제될 노드의 자식이 2개일 때
                오른쪽 subtree에서 가장 값이 작은 노드를 삭제될 노드 위치로 가져온다.
                 */
                else
                {
                    TreeNode<T>* minNode = findMinNode(currentNode->right);
                    orignalColor = minNode->color;
                    newChild = minNode->right;
                    
                    if (minNode->parent == currentNode)
                    {
                        newChild->parent = minNode;
                    }
                    else
                    {
                        transPlant(minNode, minNode->right);
                        minNode->right = currentNode->right;
                        minNode->right->parent = minNode;
                    }
                    
                    transPlant(currentNode, minNode);
                    minNode->left = currentNode->left;
                    minNode->left->parent = minNode;
                    minNode->color = currentNode->color;
                }
                currentNode->left = currentNode->right = nullptr;
                delete currentNode;
                /**
                    삭제된 노드의 위치를 대신하는 노드의 색깔을 검정색으로 칠해준다.
                    대신 하는 노드의 색깔이 빨강 → 검정이면 아무것도 하지 않아도 됨.
                    대신 하는 노드의 색깔이 검정 → 검정이면 이중 흑색 노드가 됨.
                    이중 흑색 노드는 노드들을 재배치 해주어야 함.
                 */
                if (orignalColor == COLOR::BLACK)
                {
                    eraseFixUp(newChild);
                }
                --treeSize;
                
                return true;
            }
        }
        return false;
    }
    
    /**
     삭제된 노드의 색깔이 빨강색일 경우 아무것도 하지 않아도 됨.
     
     하지만,
     삭제된 노드의 색깔이 검정색이고, 이중 흑색 노드가 만들어지면 4가지 상황이 발생할 수 있음.
     case 1. 이중 흑색 노드의 형제 노드가 빨강색인 경우.
     case 2. 이중 흑색 노드의 형제가 검정색이고, 형제의 자식노드들이 모두 검정색인 경우.
     case 3. 이중 흑색 노드의 형제가 검정색이고, 형제의 왼쪽 자식이 빨강, 오른쪽 자식이 검정인 경우.
     case 4. 이중 흑색 노드의 형제가 검정색이고, 형제의 왼쪽 자식이 검정, 오른쪽 자식이 빨강인 경우.
     */
    void eraseFixUp(TreeNode<T>* node)
    {
        TreeNode<T>* brother;

        while (node != root && node->color == COLOR::BLACK)
        {
            /**
             이중 흑색 노드가 부모의 왼쪽 자식일 때.
             */
            if (node == node->parent->left)
            {
                brother = node->parent->right;

                /**
                 case 1:
                    step 1. 형제의 색깔을 검정색으로 바꿔준다,
                    step 2. 부모의 색깔을 빨강색으로 바꿔준다.
                    step 3. 부모를 기준으로 왼쪽 회전을 적용한다.
                    step 4. 이후 case2, case3, case4를 진행한다.
                 */
                if (brother->color == RED)
                {
                    brother->color = COLOR::BLACK;
                    node->parent->color = COLOR::RED;
                    leftRotate(node->parent);
                    brother = node->parent->right;
                }

                /**
                  case 2:
                    step 1. 형제의 색깔을 빨강색으로 바꾼다.
                    step 2. 이중 흑색 노드의 black1개를 부모로 넘긴다.
                 */
                if (brother->left->color == COLOR::BLACK && brother->right->color == COLOR::BLACK)
                {
                    brother->color = COLOR::RED;
                    node = node->parent;
                }
                else
                {
                    /**
                     case 3:
                        step 1. 형제의 색깔을 빨강색으로 바꾼다.
                        step 2. 형제의 왼쪽 자식의 색깔을 검정색으로 바꾼다.
                        step 3. 형제를 기준으로 오른쪽 회전을 적용한다.
                        step 4. 새로운 형제를 지정해준다.
                            ↑case 4로 만들어줌.
                     */
                    if (brother->right->color == COLOR::BLACK)
                    {
                        brother->color = COLOR::RED;
                        brother->left->color = COLOR::BLACK;
                        rightRotate(brother);
                        brother = node->parent->right;
                    }
                    
                    /**
                     case 4:
                        step 1. 형제의 색을 부모의 색깔로 변경.
                        step 2. 부모의 색깔을 검정색으로 변경.
                        step 3. 형제의 오른쪽 자식의 색깔을 검정색으로 변경.
                        step 4. 부모를 기준으로 왼쪽 회전 적용.
                     */
                    brother->color = node->parent->color;
                    node->parent->color = COLOR::BLACK;
                    brother->right->color = COLOR::BLACK;
                    leftRotate(node->parent);
                    node = root;
                }
            }
            /**
             이중 흑색 노드가 부모의 오른쪽 자식일 때.
             */
            else
            {
                brother = node->parent->left;
                
                if (brother->color == RED)
                {
                    brother->color = COLOR::BLACK;
                    node->parent->color = COLOR::RED;
                    rightRotate(node->parent);
                    brother = node->parent->left;
                }

                if (brother->left->color == COLOR::BLACK && brother->right->color == COLOR::BLACK)
                {
                    brother->color = COLOR::RED;
                    node = node->parent;
                }
                else
                {
                    if (brother->left->color == COLOR::BLACK)
                    {
                        brother->color = COLOR::RED;
                        brother->right->color = COLOR::BLACK;
                        leftRotate(brother);
                        brother = node->parent->left;
                    }

                    brother->color = node->parent->color;
                    node->parent->color = COLOR::BLACK;
                    brother->left->color = COLOR::BLACK;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        
        node->color = COLOR::BLACK;
        root->color = COLOR::BLACK;
    }
};
