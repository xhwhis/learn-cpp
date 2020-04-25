#include <iostream>
using namespace std;

template<typename T>
T add(T a, T b) {
    cout << "add function: " << sizeof(T) << endl;
    static int i = 0;
    cout << "i = " << (++i) << endl;
    return a + b;
}

template<>
int add(int a, int b) {
    cout << ""
}

template<typename T>
class Array {
public:
    Array(int n) : n(n) {
        this->p = new T[n];
    }
    T &operator[](int ind) {
        if (ind < 0 || ind >= n) return this->__end;
        return this->p[ind];
    }
private:
    T *p;
    int n;
    T __end;
};

template<>
class Array<double> {
public:

}

template<typename T>
ostream &operator<<(ostream &output, const Array<int> &a) {
    return output;
}

int main() {
    cout << add(2, 3) << endl;
    cout << add(2.3, 4.5) << endl;
    cout << add<double>(2.3, 4) << endl;
    Array<int> a(10);
    Array<double> b(10);
    return 0;
}
