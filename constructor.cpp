#include <iostream>
using namespace std;

struct A {
    A() : next(nullptr) {
        cout << this << " default constructor" << endl;
    }
    A(A *obj) {
        this->next = obj;
        this->next->arr = new int[1000];
    }
    A(int n) : next(nullptr) {
        cout << this << " an int constructor" << endl;
        x = n, y = n;
    }
    A(const A &obj) : next(nullptr) {
        cout << this << " copy constructor" << endl;
        this->x = obj.x, this->y = obj.y;
    }
    void output() {
        cout << this->x << " " << this->y << endl;
    }
    int x, y;
    int *arr;
    A *next;
    ~A() {
        if (this->next) {
            delete this->next->arr;
        }
        cout << this << " destructor" << endl;
    }
};

void func(int &x) {
    x += 5;
}

A aa;
A bb(&aa);
A cc(&bb);

int main() {
    int n = 7;
    func(n);
    cout << n << endl;
    cout << "pre position" << endl;
    A a;
    A b = 8;
    A c(a);
    cout << "a = " << &a << endl;
    cout << "b = " << &b << endl;
    cout << "c = " << &c << endl;
    cout << "aa = " << &aa << endl;
    cout << "bb = " << &bb << endl;
    cout << "cc = " << &cc << endl;
    b.output();
    b = 6;
    b.output();
    cout << "next position" << endl;
    return 0;
}
