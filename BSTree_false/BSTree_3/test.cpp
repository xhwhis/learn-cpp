#include <iostream>
#include "BSTree.h"
using namespace std;

int main() {
    BSTree<int> a;
    for (int i = 0; i < 10; i++) {
        a.insert(i);
    }
    a.output();
    for (int i = 0; i < 10; i++) {
        cout << "a[" << i << "] = "<< a[i] << endl;
    }
    cout << "find 5: " << a.find(5) << endl;
    cout << "find 10: " << a.find(10) << endl;
    a.erase(5);
    cout << "after erase 5: " << endl;
    a.output();
    a.insert(5);
    a.clear();
    a.output();
    BSTree<char> b;
    for (char i = 'a'; i < 'a' + 10; i++) {
        b.insert(i);
    }
    b.output();
    cout << "find e: " << b.find('e') << endl;
    b.erase('e');
    cout << "after erase 'e':" << endl;
    b.output();
    b.clear();
    return 0;
}
