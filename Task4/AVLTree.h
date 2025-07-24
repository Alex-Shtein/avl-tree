#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <vector>
#include <iostream>
#include <iterator>
#include <iomanip>

template <typename T>
class AVLTree
{
private:
    class Node
    {
    public:
        Node(const T &key, Node *left, Node *right);
        ~Node();
        T GetKey();
        Node *GetLeft();
        Node *GetRight();
        int GetHeight();
        void SetKey(const T &key);
        void SetLeft(Node *left);
        void SetRight(Node *right);
        void SetHeight(int height);

    private:
        T _key;
        Node *_left;
        Node *_right;
        int _height;
    };
    Node *_root;
    AVLTree operator=(const AVLTree &tree) {};
    AVLTree operator=(AVLTree &&tree) {};
    Node *Find(const T &key);
    int Height(Node *node);
    int GetBalance(Node *node);
    Node *RemoveR(const T &key, Node *node);
    Node *InsertR(const T &key, Node *node);
    Node *RightRotate(Node *node);
    Node *LeftRotate(Node *node);
    Node *FindMin(Node *node);
    Node *Rotate(Node *node);

public:
    AVLTree();
    AVLTree(T *arr, int size);
    AVLTree(const AVLTree<T> &tree);
    AVLTree(AVLTree &&tree);
    ~AVLTree();
    bool Insert(const T &key);
    bool Remove(const T &key);
    bool Contains(const T &key);
    bool Empty();
    std::vector<T> RoundLrootR();
    std::vector<T> RoundRrootL();
    void Output();
};

#include "impl/AVLTree.h"

#endif