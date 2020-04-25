#include <iostream>
using namespace std;

void f(int &x) {
    cout << x << " is left value" << endl;
    return ;
}

void f(int &&x) {
    cout << x << " is right value" << endl;
    return ;
}

int main() {
    int n = 123;
    cout << (++n)++ << endl;
    cout << n << endl;
    f(n++);
    f(move(++n));
    return 0;
}
