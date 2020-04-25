#include <iostream>
using namespace std;

class B;
class C;
class D;
class E;
class F;

class A {
public:
    class IVistor {
    public:
        virtual void visit(A *) = 0;
        virtual void visit(B *) = 0;
        virtual void visit(C *) = 0;
        virtual void visit(D *) = 0;
        virtual void visit(E *) = 0;
    };
    virtual void Accept(IVistor *vis) {
        vis->visit(this);
    }
    virtual ~A() {}
};

class B : public A {};
class C : public A {};
class D : public A {};
class E : public A {};
class F : public A {};

class PriVisitor : public A::IVistor {
public: 
    virtual void visit(B *obj) {
        cout << "class B" << endl;
    }
    virtual void visit(C *obj) {
        cout << "class C" << endl;
    }
    virtual void visit(D *obj) {
        cout << "class D" << endl;
    }
    virtual void visit(E *obj) {
        cout << "class E" << endl;
    }
    virtual void visit(F *obj) {
        cout << "class F" << endl;
    }
};

class CalVisitor : public A::IVistor {
public:
    CalVisitor(int val = 1) : val(val) {}
    virtual void visit(B *obj) {
        val += 5;
    }
    virtual void visit(C *obj) {
        val *= 2;
    }
    virtual void visit(D *obj) {
        val -= 4;
    }
    virtual void visit(E *obj) {
        val += 6;
    }
    virtual void visit(F *obj) {
        val -= 7;
    }
    int val;
};

int main() {
    srand(time(0));
    A *arr[10];
    for (int i = 0; i < 10; i++) {
        switch (rand() % 5) {
            case 0: arr[i] = new B(); break;
            case 1: arr[i] = new C(); break;
            case 2: arr[i] = new D(); break;
            case 3: arr[i] = new E(); break;
            case 4: arr[i] = new F(); break;
        }
    }
    CalVisitor vis;
    for (int i = 0; i < 10; i++) {
        vis.visit(arr[i]);
    }
    cout << vis.val << endl;
    return 0;
}
