#include <iostream>
using namespace std;

struct A {
    A() {
        x = 0xaaaaaaaa;
        y = 0xaaaaaaaa;
    }
    int x, y;
};

struct B : virtual A {
    B() {
        z = 0xbbbbbbbb;
    }
    int z;
    void outputB() {
        cout << this->x << endl;
        cout << this->y << endl;
        cout << this->z << endl;
    }
};

struct C : virtual A {
    C() {
        z = 0xcccccccc;
    }
    int z;
    void outputC() {
        cout << this->x << endl;
        cout << this->y << endl;
        cout << this->z << endl;
    }
};

struct E : virtual A {
    E() {
        z = 0xeeeeeeee;
    }
    int z;
    void outputE() {
        cout << this->x << endl;
        cout << this->y << endl;
        cout << this->z << endl;
    }
};

struct D : B, C, E {
    D() {
        w = 0xdddddddd;
    }
    int w;
};

template<typename T>
void output(T &&a, int output_cnt = -1) {
    cout << "begin address : " << ((void *)&a) << endl;
    int cnt;
    if (output_cnt == -1) cnt = sizeof(a);
    else cnt = output_cnt;
    printf("size : %d\n", cnt);
    unsigned char *p = (unsigned char *)&a;
    for (int i = 0; i < cnt; i++) {
        printf("%02X ", p[i]);
        if ((i + 1) % 8 == 0) printf("\n");
    }
    printf("\n");
    return ;
}

int main() {
    B b;
    b.x = 0x11111111;
    b.y = 0x22222222;
    b.z = 0x33333333;
    output(b);
    A *p = &b;
    D d;
    cout << "object d : " << sizeof(d) << endl;
    output(d);
    A *pa = &d;
    C *pc = &d;
    B *pb = &d;
    E *pe = &d;
    cout << endl << "output d :" << endl;
    cout << ((void **)&d)[0] << endl;
    output(((unsigned char **)&d)[0][0], 32);
    cout << endl << "output pb :" << endl;
    output(*pb);
    output(((unsigned char **)pb)[0][0], 32);
    cout << endl << "output pc :" << endl;
    output(*pc);
    output(((unsigned char **)pc)[0][0], 32);
    cout << endl << "output pe :" << endl;
    output(*pe);
    output(((unsigned char **)pe)[0][0],32);
    output(((unsigned int ***)pe)[0][0][0], 16);
    output(((unsigned int ***)pe)[0][1][0], 32);
    output(((unsigned int ***)pe)[0][2][0], 16);
    output(((unsigned int ***)pe)[0][3][0], 16);
    pa->x = 1;
    pa->y = 2;
    d.outputB();
    d.outputC();
    return 0;
}
