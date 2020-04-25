#include <iostream>
using namespace std;

class A {
public :
    A(int x) {
        cout << "class A's constructor" << endl;
    }
};

class Point {
public :
    Point();
    Point(int x, int y);
    int x() const;
    int y() const;
    int x_cnt() const;
    void set_x(int x);
    void set_y(int y);
    static int output_cnt();
    ~Point();

private :
    static int point_cnt;
    int __x, __y;
    mutable int __x_cnt;
    A __a;
};

int Point::point_cnt = 0;

int Point::output_cnt() {
    return Point::point_cnt;
}

Point::Point() : __x_cnt(0), __a(2) {
    Point::point_cnt += 1;
}

Point::Point(int x, int y) : 
    __x(x), __y(y), 
    __x_cnt(0), __a(4) {
    Point::point_cnt += 1;
}

Point::~Point() {
    Point::point_cnt -= 1;
}

int Point::x() const {
    this->__x_cnt += 1;
    return this->__x;
}

int Point::y() const {
    return this->__y;
}

int Point::x_cnt() const {
    return this->__x_cnt;
}

void Point::set_x(int x) {
    this->__x = x;
}

void Point::set_y(int y) {
    this->__x = y;
}

void func() {
    Point c, d;
    cout << "func : " << Point::output_cnt() << endl;
    return ;
}

int main() {
    Point a(2, 3), b;
    const Point c(3, 4);
    cout << a.x() << " " << a.y() << endl;
    cout << c.x() << " " << c.y() << endl;
    cout << c.x() << " " << c.y() << endl;
    cout << a.x_cnt() << " " << b.x_cnt() << " " << c.x_cnt() << endl;
    cout << "befor func : " << Point::output_cnt() << endl;
    func();
    cout << "after func : " << Point::output_cnt() << endl;
    return 0;
}
