#include "my_vector.h"

int main() {
    Vector<int> v1(3,1);
    v1.print();
    for(int i = 0; i < 10; i++) {
        v1.push_back(i);
    }
    v1.print();
    v1.pop_back();
    v1.print();
    v1[3] = 597;
    v1.print();
    v1.insert(5,1024);
    v1.print();
    cout << "v1.size() = " << v1.size() << endl;
    cout << "v1.at(3) = " << v1.at(3) << endl;
    cout << "v1.front() = " << v1.front() << endl;
    cout << "v1.back() = " << v1.back() << endl;
    v1.assign(3, 3);
    v1.print();
    Vector<int> v2(v1);
    v2.print();
    Vector<int> v3;
    v3 = v1;
    v3.print();
    cout << "v1.empty() " << (v1.empty() ? "yes" : "no") << endl;
    v1.clear();
    cout << "v1.empty() " << (v1.empty() ? "yes" : "no") << endl;
    Vector<int> v4(3);
    v2.swap(v4);
    v2.print();
    v4.print();
    return 0;
}
