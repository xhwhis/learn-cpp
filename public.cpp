#include <iostream>
using namespace std;

struct A {
    int x, y;
    void echo() {
        cout << "hello world a" << endl;
        return ;
    }
};

struct B {
    private:
    int x, y;
    public:
    void set_xy(int x, int y) {
        cout << this << endl;
        this->x = x, this->y = y;
    }
    void echo() {
        cout << "hello world b" << endl;
        cout << x << " " << y << endl;
        return ;
    }
};

int main() {
    A a;
    B b;
    a.x = 1, a.y = 2;
    b.set_xy(3, 4);
    cout << &b << endl;
    cout << a.x << " " << a.y << endl;
    b.echo();
    return 0;
}
