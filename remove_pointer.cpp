#include <iostream>
using namespace std;

template<typename T>
struct my_remove_pointer {
    typedef T type;
};

template<typename T>
struct my_remove_pointer<T*> {
    typedef T type;
};

template<typename T>
struct my_remove_pointer<T* const> {
    typedef T type;
};

template<typename T>
struct my_remove_pointer<T* volatile> {
    typedef T type;
};

template<typename T>
struct my_remove_pointer<T* const volatile> {
    typedef T type;
};

int main() {

    return 0;
}
