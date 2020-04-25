#include <iostream>
using namespace std;

void f(int x) {
    cout << x << endl;
    return ;
}

void f(int *p) {
    cout << p << endl;
    return ;
}

int main() {
    int n = 123;
    f(n);
    f(&n);
    f(nullptr);
    return 0;
}
