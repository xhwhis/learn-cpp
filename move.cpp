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
typename remove_reference<T>::type &&my_move(T &&a) {
    return static_cast<typename remove_reference<T>::type &&>(a);
}

int main() {
    int a = 123;
    f(a);
    f(my_move(a));
    return 0;
}
