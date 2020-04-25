#ifndef _MY_SET_H
#define _MY_SET_H

#include <cstring>

template<typename T>
class Node {
public:
    T val;
    Node<T> *lchild, *rchild;
    int n;

    Node(int val, int n) : val(val), lchild(NULL), rchild(NULL), n(n){}

};

template<typename T>
class Tree {
public:
    Node<T> *root;
    int n;
    T *arr;
    int capacity;

    Tree() : root(NULL), n(0), capacity(20) {
        this->arr = new T[this->capacity];
    }

};

template<typename T>
class Set {
public:
    Tree<T> *tree;

    Node<T> *insertNode(Node<T> *root, T val, int *flag) {
        if (root == NULL) {
            *flag = 1;
            Node<T> *p = new Node<T>(val, this->tree->n);
            if (this->tree->n == this->tree->capacity) {
                this->tree->capacity += 20;
                T *tmp = new T[this->tree->capacity];
                memcpy(tmp, this->tree->arr, sizeof(T) * this->tree->n);
                delete[] this->tree->arr;
                this->tree->arr = tmp;
            }
            this->tree->arr[this->tree->n] = val;
            return p;
        }
        if (root->val == val) return root;
        else if (root->val > val) root->lchild = insertNode(root->lchild, val, flag);
        else root->rchild = insertNode(root->rchild, val, flag);
        return root;
    }
    
    void insert(T val) {
        int flag = 0;
        this->tree->root = insertNode(this->tree->root, val, &flag);
        this->tree->n += flag;
        return ;
    }

    T &operator[](int n) {
        return this->tree->arr[n];
    }
};

#endif
