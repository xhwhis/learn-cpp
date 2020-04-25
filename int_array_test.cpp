/*************************************************************************
	> File Name: int_array.cpp
	> Author: Cantredo
	> Mail: aimingco@gmail.com
	> Created Time: 2020年02月26日 星期三 20时07分56秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <set>
#define MAXN 4
#define MOD 10

using namespace std;

class IntArray {
private:
    int size, *arr;
    static int quick_pow(int, int);
    static int binary_search(int, int, int, int []);
    static void find_intersection(set<int> &, set<int> &, IntArray &);

public:
    IntArray();
    IntArray(int);
    IntArray(const IntArray &);
    int &operator[](int);
    void operator+=(int);
    IntArray &operator++();    //++ a
    IntArray operator++(int);  //a ++
    
    void operator^=(int);      //每个元素的n次方 a ^= n;
    int operator()(int);       //查找括号内的数的下标, a(1)
    IntArray operator&(const IntArray &);   //找两个数组的交集, c = a & b;
    IntArray operator|(const IntArray &);   //找两个数组的并集, c = a | b;
    IntArray operator-(const IntArray &);   //找两个数组的差集, c = a - b; (属于a不属于b)
    friend void operator*=(const IntArray &, int);  //每个元素的n倍, a *= n;
    friend IntArray operator+(const IntArray &, const IntArray &);  //数组拼接, c = a + b
    friend IntArray &operator--(IntArray &);    //-- a
    friend IntArray operator--(IntArray &, int);    //a --
    friend IntArray operator*(const IntArray &, int);   //每个元素的n倍, c = a * n;
    friend istream &operator>>(istream &, const IntArray &);    //往a中输入, cin >> a

    friend ostream &operator<<(ostream &, const IntArray &);
    ~IntArray();
};

IntArray::IntArray() {}

IntArray::IntArray(int size) : size(size) {
    this->arr  = new int[size];
}

IntArray::IntArray(const IntArray &obj) {
    this->size = obj.size;
    this->arr  = new int[this->size];
    for (int i = 0; i < this->size; ++ i) {
        this->arr[i] = obj.arr[i];
    }
    // memcpy(this->arr, obj.arr, sizeof(int) * this->size);
}

IntArray::~IntArray() {
    delete []arr;
}

int& IntArray::operator[](int ind) {
    if (ind >= 0) return this->arr[ind];
    return this->arr[this->size + ind];
}

void IntArray::operator+=(int n) {
    for (int i = 0; i < this->size; ++ i) {
        this->arr[i] += n;
    }
    return ;
}

IntArray& IntArray::operator++() {
    for (int i = 0; i < this->size; ++ i) {
        this->arr[i] += 1;
    }
    return (*this);
}

IntArray IntArray::operator++(int x) {
    IntArray ret = (*this);
    for (int i = 0; i < this->size; ++ i) {
        this->arr[i] += 1;
    }
    return ret;
}

IntArray &operator--(IntArray &a) {
    for (int i = 0; i < a.size; ++ i) {
        a.arr[i] -= 1;
    }
    return a;
}

IntArray operator--(IntArray &a, int n) {
    IntArray res = a;
    for (int i = 0; i < a.size; ++ i) {
        a.arr[i] -= 1;
    }
    return res;
}

int IntArray::quick_pow(int a, int n) {
    int ans = 1, base = a;
    while (n) {
        if (n & 1) ans *= base;
        base *= base;
        n >>= 1;
    }
    return ans;
}

void IntArray::operator^=(int n) {
    for (int i = 0; i < this->size; ++ i) {
        this->arr[i] = quick_pow(this->arr[i], n);
    }
    return ;
}

int IntArray::binary_search(int l, int r, int n, int arr[]) {
    while (l < r) {
        int mid = (l + r) >> 1;
        if (arr[mid] > n) r = mid;
        else if (arr[mid] < n) l = mid + 1;
        else return mid;
    }
    return -1;
}

int IntArray::operator()(int n) {    
    return binary_search(0, this->size, n, this->arr);
}

void IntArray::find_intersection(set<int> &less, set<int> &more, IntArray &res) {
    int ind = 0;
    for (auto i : less) {
        if (more.find(i) != more.end()) {
            res.arr[ind ++] = i;
        }
    }
    res.size = ind;
    return ;
}

IntArray IntArray::operator&(const IntArray &a) {
    set<int> s1(this->arr, this->arr + this->size);
    set<int> s2(a.arr, a.arr + a.size);
    IntArray res(min(s1.size(), s2.size()));
    if (s1.size() < s2.size()) find_intersection(s1, s2, res);
    else find_intersection(s2, s1, res);
    return res;
}

IntArray IntArray::operator|(const IntArray &a) {
    set<int> union_set(this->arr, this->arr + this->size);
    for (int i = 0; i < a.size; ++ i) {
        union_set.insert(a.arr[i]);
    }
    IntArray res(union_set.size());
    int ind = 0;
    for (auto i : union_set) {
        res.arr[ind ++] = i;
    }
    res.size = ind;
    return res;
}

IntArray IntArray::operator-(const IntArray &a) {
    set<int> s1(this->arr, this->arr + this->size);
    set<int> s2(a.arr, a.arr + a.size);
    IntArray res(max(this->size, a.size));
    int ind = 0;
    for (auto i : s1) {
        if (s2.find(i) == s2.end()) {
            res.arr[ind ++] = i;
        }
    }
    res.size = ind;
    return res;
}

void operator*=(const IntArray &a, int n) {
    for (int i = 0; i < a.size; ++ i) {
        a.arr[i] *= n;
    }
    return ;
}

IntArray operator+(const IntArray &a, const IntArray &b) {
    IntArray res(a.size + b.size);
    for (int i = 0; i < a.size; ++ i) {
        res.arr[i] = a.arr[i];
    }
    for (int i = 0; i < b.size; ++ i) {
        res.arr[a.size + i] = b.arr[i];
    }
    return res;
}

IntArray operator*(const IntArray &a, int n) {
    IntArray res = a;
    for (int i = 0; i < a.size; ++ i) {
        res.arr[i] *= n;
    }
    return res;
}

istream &operator>>(istream &in, const IntArray &obj) {
    for (int i = 0; i < obj.size; ++ i) {
        in >> obj.arr[i];
    }
    return in;
}

ostream &operator<<(ostream &out, const IntArray &obj) {
    out << "<class IntArray> : ";
    for (int i = 0; i < obj.size; ++ i) {
        out << obj.arr[i] << " ";
    }
    return out;
}

int main() {
    srand(time(0));
    IntArray a(MAXN);
    IntArray b(MAXN >> 1);
    b[0] = 3, b[1] = 5;
    for (int i = 0; i < MAXN; ++ i) {
        a[i] = i + 1;
    }
    /*
    cout << a[4] << endl;
    cout << a[-2] << endl;  //输出倒数第二位的值
    cout << a << endl;  //输出整个数组中的元素
    a += 5; //给数组中所有元素都加5
    cout << a << endl;  //输出整个数组中的元素
    cout << (a ++) << endl;  //给数组中所有元素加1
    cout << (++ a) << endl;  //同上
    */ 
    cout << "a :" << endl << a << endl;
    cout << "b :" << endl << b << endl;

    cout << endl << "index = "<< a(3) << endl << endl;  //寻找元素3的下标
    IntArray c = a & b;  //求交集
    cout << "交集 ：" << endl << c << endl;
    IntArray d = a | b;  //求并集
    cout << "并集 ：" << endl << d << endl;
    IntArray e = a - b;  //求差集
    cout << "差集 ：" << endl << e << endl;
    IntArray f = a + b;  //数组拼接
    cout << "拼接 ：" << endl << f << endl;
    a *= 2;              //a中每个元素的2倍
    cout << "after ：" << endl << a << endl;
    IntArray g = a * 2;  //a中每个元素的2倍
    cout << "after ：" << endl << g << endl;
    b ^= 2;              //b中每个元素的2次方
    cout << "after ：" << endl << b << endl;
    cout << "after : " << endl << (b ++) << endl;   //b++
    cout << "after : " << endl << (++ b) << endl;   //++b
    cout << "input : ";
    cin >> b;            //往b中输入
    cout << "after : " << endl << b << endl;
    return 0;
}
