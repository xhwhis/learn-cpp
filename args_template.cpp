#include <iostream>
using namespace std;

template<typename T>
void print(const T &a) {
    cout << a << endl;
}

template<typename T, typename ...ARGS>
void print(const T &a, ARGS ...args) {
    cout << a << " ";
    print(args...);
    return ;
}

template<typename T, typename ...ARGS>
struct ARG {
    typedef T getT;
    typedef ARG<ARGS...> rest;
};

template<typename T>
struct ARG<T> {
    typedef T getT;
};

template<typename T, typename ...ARGS> class Test;
template<typename T, typename ...ARGS>
class Test<T(ARGS...)> {
public:
    T operator()(typename ARG<ARGS...>::getT a, typename ARG<ARGS...>::rest::getT b) {
        return a + b;
    }
};

int main() {
    print(123, "hello world", 26.23, 'c');
    cout << sizeof(ARG<int, double, float>::getT) << endl;
    cout << sizeof(ARG<int, double, float>::rest::getT) << endl;
    cout << sizeof(ARG<int, double, float>::rest::rest::getT) << endl;
    ARG<int, double, float>::getT a = 123;
    ARG<int, double, float>::rest::getT b = 12.3;
    ARG<int, double, float>::rest::rest::getT c = 123.34;
    cout << a << " " << b << " " << c << endl;
    Test<int(double, float)> d;
    cout << d(2.3, 4.5) << endl;
    return 0;
}
