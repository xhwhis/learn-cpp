#include <iostream>
using namespace std;

template<typename T>
struct add_const {
    typedef const T type;
};

int main() {
    return 0;
}
