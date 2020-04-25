#include <iostream>
#include "thread_pool.h"
using namespace std;

void func(int a, int &b) {
    b++;
    cout << "func: " << a << " " << b << endl;
    cout << "func: ";
    cout << a;
    cout << " ";
    cout << b;
    cout << endl;
}

int main() {
    int a = 1;
    haizei::Task t(func, 2, ref(a));
    t.run();
    cout << a << endl;
    return 0;
}
