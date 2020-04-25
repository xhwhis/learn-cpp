#include <iostream>
using namespace std;

template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

template<typename T, typename U>
auto add(T *a, U *b) -> decltype(add(*a, *b)) {
    return add(*a, *b);
}

int main() {
    cout << add(2, 3.4) << endl;
    return 0;
}
