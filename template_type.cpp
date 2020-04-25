#include <iostream>
using namespace std;

template<typename T>
void my_swap(T &&a, T &&b) {
    typename remove_reference<T>::type c = a;
    a = b;
    b = c;
    return ;
}

template<typename T>
void add(T &&a, T &&b) {
    a += 1;
    b += 2;
    return ;
}

int main() {
    int a = 1, b = 2;
    cout << a << " " << b << endl;
    my_swap(a, b);
    cout << a << " " << b << endl;
    my_swap(move(a), move(b));
    cout << a << " " << b << endl;
    add(a, b);
    cout << a << " " << b << endl;
    add(move(a), move(b));
    cout << a << " " << b << endl;
    return 0;
}
