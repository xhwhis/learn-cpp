#ifndef _BSTREE_H
#define _BSTREE_H

#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T val;
    Node<T> *lchild, *rchild;
    
    Node(const T& val) : val(val), lchild(NULL), rchild(NULL) {}
};

template<typename T>
class BSTree {
public:
    Node<T> *__root;
    int size;
    T *arr;

    BSTree() : __root(NULL), size(0) {}

    ~BSTree() { delete this->__root; }

    Node<T>* &root() { return this->__root; }
    
    void __clear(Node<T>* &node) {
        if (node == NULL) return ;
        __clear(node->lchild);
        __clear(node->rchild);
        delete node;
        node = NULL;
    }

    void clear() {
        __clear(this->root());
    }

    /*bool __find(Node<T>* &node, T val, Node<T>* p, Node<T>* &where) {
        if (node == NULL) {
            where = p;
            return 0;
        }
        if (val == node->val) {
            where = node;
            return 1;
        } else if (val < node->val) {
            return __find(node->lchild, val, node, where);
        } else {
            return __find(node->rchild, val, node, where);
        }
    }*/

    int find(T val) {
        int left = 0, right = this->size, mid;
        while (left <= right) {
            mid = (left + right) >> 1;
            if (this->arr[mid] == val) return mid;
            else if (this->arr[mid] > val) right = mid - 1;
            else left = mid + 1;
        }
        return -1;
    }

    void __insert(Node<T>* &node, T val) {
        if (node == NULL) {
            node = new Node<T>(val);
            this->size++;
            return ;
        }
        if (node->val == val) {
            return ;
        }
        if (__root->val > val) {
            __insert(node->lchild, val);
        } else {
            __insert(node->rchild, val);
        }
        return ;
    }

    void insert(T val) {
        __insert(this->root(), val);
        return ;
    }

    void __erase(Node<T>* &node, T val) {
        if (node == NULL) return ;
        if (val == node->val) {
            if (node->lchild == NULL || node->rchild == NULL) {
                Node<T> *temp = node->lchild ? node->lchild : node->rchild;
                delete node;
                node = temp;
            } else {
                Node<T> *p = node->lchild, *temp;
                while (p->rchild) {
                    temp = p;
                    p = p->rchild;
                }
                node->val = p->val;
                if (node == temp) {
                    temp->lchild = p->lchild;
                } else {
                    temp->rchild = p->lchild;
                }
                delete p;
            }
            size--;
        } else if (val < node->val) {
            return __erase(node->lchild, val);
        } else {
            return __erase(node->rchild, val);
        }
    }
    
    void erase(T val) {
        __erase(this->root(), val);
        return ;
    }

    void _output(Node<T>* &node, int &ind) {
        if (node == NULL) return ;
        _output(node->lchild, ind);
        cout << " " << node->val;
        arr[ind++] = node->val;
        _output(node->rchild, ind);
        return ;
    }

    void __output(Node<T>* &node) {
        cout << "in_order output:";
        int ind = 0;
        arr = new T[this->size + 5];
        _output(node, ind);
        cout << endl;
        return ;
    }
    
    void output() {
        __output(this->root());
    }

    T &operator[](int ind) {
        return this->arr[ind];
    }
};

#endif
