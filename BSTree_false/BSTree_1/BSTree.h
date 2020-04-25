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

/*template<typename T>
class Tree {
public:
    Node<T> *__root;
};*/

template<typename T>
class BSTree {
public:
    Node<T> *__root;
    int size;

    BSTree() : __root(NULL), size(0) {}

    ~BSTree() { delete this->__root; }

    Node<T>* &root() { return this->__root; }
    
    void clear(Node<T>* &node) {
        if (node == NULL) return ;
        clear(node->lchild);
        clear(node->rchild);
        delete node;
        size--;
    }

    bool find(Node<T>* &node, T val, Node<T>* p, Node<T>* &where) {
        if (node == NULL) {
            where = p;
            return 0;
        }
        if (val == node->val) {
            where = node;
            return 1;
        } else if (val < node->val) {
            return find(node->lchild, val, node, where);
        } else {
            return find(node->rchild, val, node, where);
        }
    }

    Node<T>* insert(Node<T>* &node, T val) {
        /*Node<T> *where, *node;
        if (find(this->__root, val, NULL, where)) return ;
        node = new Node<T>(val);
        if (where == NULL) {
            this->__root = node;
        } else if (val < where->val) {
            where->lchild = node;
        } else {
            where->rchild = node;
        }
        size++;
        return ;*/

        if (node == NULL) {
            Node<T> *p = new Node<T>(val);
            return p;
        }
        if (node->val == val) {
            return node;
        }
        if (__root->val > val) {
            node->lchild = insert(node->lchild, val);
        } else {
            node->rchild = insert(node->rchild, val);
        }
        return node;
    }

    void erase(Node<T>* &node, T val) {
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
            return erase(node->lchild, val);
        } else {
            return erase(node->rchild, val);
        }
    }

    void __output(Node<T>* &node) {
        if (node == NULL) return ;
        __output(node->lchild);
        cout << " " << node->val;
        __output(node->rchild);
        return ;
    }

    void output(Node<T>* &node) {
        cout << "in_order output:";
        __output(node);
        cout << endl;
        return ;
    }
};

#endif
