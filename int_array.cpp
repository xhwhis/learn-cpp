#include <iostream>
#include <algorithm>
using namespace std;

class intArray {
private:
    int n;
    int *p;
public:
    intArray(int n) : n(n) {
        this->p = new int[n];
    }
    intArray(const intArray &obj) : n(obj.n) {
        this->p = new int[n];
        for (int i = 0; i < n; i++) {
            this->p[i] = obj.p[i];
        }
    }
    int size() {
        return n;
    }
    int find(int num) {
        for (int i = 0; i < n; i++) {
            if (p[i] == num) return i;
        }
        return -1;
    }
    void sort(int op) {
        if (op) std::sort(p, p + n);
        else std::sort(p, p + n, [](int a, int b) {return a > b;});
        return ;
    }
    void reverse() {
        std::reverse(p, p + n);
        return ;
    }
    int &operator[](int ind) {
        if (ind < 0) return this->p[n + ind];
        return this->p[ind];
    }
    intArray operator+(int num) {
        intArray ret = *this;
        for (int i = 0; i < n; i++) {
            ret.p[i] = this->p[i] + num;
        }
        return ret;
    }
    intArray operator+(intArray a) {
        intArray ret = *this;
        ret.n = this->n + a.n;
        ret.p = new int[ret.n];
        for (int i = 0; i < this->n; i++) {
            ret.p[i] = this->p[i];
        }
        for (int i = this->n; i < ret.n; i++) {
            ret.p[i] = a.p[i - this->n];
        }
        return ret;
    }
    void operator+=(int num) {
        for (int i = 0; i < n; i++) {
            this->p[i] += num;
        }
        return ;
    }
    intArray &operator+=(intArray a) {
        int *temp = new int[this->n + a.n];
        for (int i = 0; i < this->n; i++) {
            temp[i] = this->p[i];
        }
        for (int i = this->n; i < this->n + a.n; i++) {
            temp[i] = a.p[i - this->n];
        }
        delete[] this->p;
        this->p = temp;
        this->n += a.n;
        return *this;
    }
    intArray &operator++() {
        for (int i = 0; i < n; i++) {
            this->p[i]++;
        }
        return *this;
    }
    intArray operator++(int x) {
        intArray ret = *this;
        for (int i = 0; i < n; i++) {
            this->p[i]++;
        }
        return ret;
    }
    friend ostream &operator<<(ostream &, const intArray &);
    ~intArray() {
        delete[] this->p;
    }
};

ostream &operator<<(ostream &output, const intArray &a) {
    output << "<class intArray>:";
    for (int i = 0; i < a.n; i++) {
        output << " " << a.p[i];
    }
    return output;
}

int main() {
    intArray a(10);
    for (int i = 0; i < 10; i++) {
        a[i] = i;
    }
    cout << "size " << a.size() << endl;
    cout << "find(3) " << a.find(3) << endl;
    cout << "a[4] " << a[4] << endl;
    cout << "a[-2] " << a[-2] << endl;
    a += 5;
    cout << "a += 5" << endl;
    cout << a << endl;
    a.sort(1);
    cout << "up sort" << endl;
    cout << a << endl;
    a.sort(0);
    cout << "down sort" << endl;
    cout << a << endl;
    a.reverse();
    cout << "reverse" << endl;
    cout << a << endl;
    cout << "a++" << endl;
    cout << (a++) << endl;
    cout << "++a" << endl;
    cout << (++a) << endl;
    cout << "a + 5" << endl;
    cout << (a + 5) << endl;
    intArray b(10);
    for (int i = 0; i < 10; i++) {
        b[i] = i;
    }
    cout << "b" << endl;
    cout << b << endl;
    cout << "a + b" << endl;
    cout << (a + b) << endl;
    a += b;
    cout << "a += b" << endl;
    cout << a << endl;
    return 0;
}
