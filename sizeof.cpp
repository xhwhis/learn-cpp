#include <stdio.h>

class A {
public:
    A() : a(0), b(0), c(0) {}
    long a;
    int b;
    long c;
    char d;
    void funcA() {}
    void funcB() {}
    void funcC() {}
};

int main() {
    A classA;
    printf ("%lu\n", sizeof(classA));
    return 0;
}
