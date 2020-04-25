#include<iostream>
using namespace std;

class Point {
public:
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point &obj) : x(obj.x), y(obj.y) {
        cout << "copy constructor" << endl;
    }
    int operator()(int num) {
        return this->x + this->y + num;
    }
    int operator[](string str) {
        if (str == "x") return this->x;
        if (str == "y") return this->y;
        return 0;
    }
    Point operator-(const Point &a) {
        Point ret;
        ret.x = this->x - a.x;
        ret.y = this->y - a.y;
        return ret;
    }
    friend ostream &operator<<(ostream &, const Point &);
    friend Point operator+(const Point &, const Point &);
private:
    int x, y;
};

Point operator+(const Point &a, const Point &b) {
    Point ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    return ret;
}

ostream &operator<<(ostream &output, const Point &a) {
    output << "<class Point>(" << a.x << ", " << a.y << ")";
    return output;
}

int main() {
    Point a(2, 4), b(5, 3);
    Point c = a + b;
    Point d = a + b + c;
    Point e = d - b;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;
    cout << e << endl;
    return 0;
}
