#include <iostream>
using namespace std;

void f(int &x) {
    cout << "left value" << endl;
    return ;
}

void f(int &&x) {
    cout << "right value" << endl;
    return ;
}

template<typename T>
struct my_add_lvalue_reference {
    typedef T& type;
};

template<typename T>
struct my_add_lvalue_reference<T&> {
    typedef T& type;
};

template<typename T>
struct my_add_lvalue_reference<T&&> {
    typedef T& type;
};

int main() {
    int a;
    f(a);
    f(a++);
    my_add_lvalue_reference<int>::type b = (a++);
    return 0;
}
