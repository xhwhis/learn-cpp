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
struct my_add_rvalue_reference {
    typedef T& type;
};

template<typename T>
struct my_add_rvalue_reference<T&> {
    typedef T& type;
};

template<typename T>
struct my_add_rvalue_reference<T&&> {
    typedef T&& type;
};

int main() {
    int a;
    f(a);
    typename my_add_rvalue_reference<int>::type b = a;
    f(b);
    return 0;
}
