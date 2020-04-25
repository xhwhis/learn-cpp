#include <iostream>
#include "BSTree.h"
using namespace std;

int main() {
    BSTree<int> a;
    for (int i = 0; i < 10; i++) {
        a.root() = a.insert(a.root(), i);
    }
    a.output(a.root());
    for (int i = 0; i < 10; i++) {
        cout << "a[" << i << "] = "<< a[i] << endl;
    }
    Node<int> *p;
    cout << (a.find(a.root(), 5, NULL, p) ? "FOUND " : "NOT FOUND ") << p->val << endl;
    a.erase(a.root(), 5);
    a.output(a.root());
    return 0;
}
