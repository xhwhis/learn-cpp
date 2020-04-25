#ifndef _MY_VECTOR_H
#define _MY_VECTOR_H

#include <iostream>
#include <cstring>
using namespace std;

template<typename T>
class Vector {
private:
    int n;
    int capacity;
    T *p;

public:
    Vector():n(0), capacity(0), p(NULL){}
    
    Vector(int n) {
        this->n = n;
        this->capacity = n + 20;
        this->p = new T[this->capacity];
    }
    
    Vector(int n,const T &data) {
        this->n = n;
        this->capacity = n + 20;
        this->p = new T[this->capacity];
        for(int i = 0; i< this->n; i++) {
            this->p[i] = data;
        }
    }

    Vector(const Vector &obj) {
        this->n = obj.n;
        this->capacity = obj.capacity;
        this->p = new T[this->capacity];
        memcpy(this->p, obj.p, this->n * sizeof(T));
    }

    ~Vector() {
        if(this->p != NULL) {
            delete[] this->p;
        }
    }
    
    int size() const {
        return this->n;
    }
    
    bool empty() const {
        return this->n;
    }

    void print() {
        if (this->p == NULL) {
            cout << "NULL" << endl;
            return ;
        }
        for(int i = 0; i < this->n; i++) {
            i && cout << ' ';
            cout << this->p[i];
        }
        cout<<endl;
        return ;
    }

    void push_back(const T &data) {
        if(this->p == NULL) {
            this->n = 0;
            this->capacity = 20;
            this->p = new T[this->capacity];
        }
        if(this->n == this->capacity) {
            this->capacity += 20;
            T *ret = new T[this->capacity];
            memcpy(ret, p, this->n * sizeof(T));
            delete[] p;
            p = ret;
        }
        this->p[this->n] = data;
        this->n++;
    }
    
    void pop_back() {
        if(this->n == 0) return ;
        this->p[this->n - 1] = 0;
        this->n--;
        return ;
    }
    
    T &at(int ind) {
        if(ind >= 0 && ind < this->n) {
            return this->p[ind];
        }
        return this->p[this->n];
    }

    T &front() {
        return this->p[0];
    }

    T &back() {
        if (this->n > 0) {
            return this->p[this->n - 1];
        }
        return this->p[this->n];
    }

    void assign(int ind, const T &data) {
        if (ind < 0 || ind >= this->n) return ;
        this->p[ind] = data;
        return ;
    }

    void insert(int ind, const T &data) {
        if(ind < 0 || ind > this->n) return ;
        if(this->n == this->capacity) {
            this->capacity += 20;
            T *ret = new T[this->capacity];
            memcpy(ret, p, this->n * sizeof(T));
            delete[] p;
            p = ret;
        }
        for(int i = this->n; i > ind; i--) {
            this->p[i] = this->p[i - 1];
        }
        this->p[ind] = data;
        this->n++;
        return ;
    }
    
    void erase(int ind) {
        if(ind < 0 || ind >= this->n) return ;
        for(int i = ind; i < this->n - 1; i++) {
            this->p[i] = this->p[i + 1];
        }
        this->n--;
        return ;
    }
    
    void swap(Vector &obj) {
        int tmp = this->n;
        this->n = obj.n;
        obj.n = tmp;
        tmp = this->capacity;
        this->capacity = obj.capacity;
        obj.capacity = tmp;
        T *tmp_p = this->p;
        this->p = obj.p;
        obj.p = tmp_p;
        return ;
    }

    void clear() {
        this->n = 0;
    }
    
    T &operator[](int ind) {
        if(ind >= 0 && ind < this->n) {
            return this->p[ind];
        }
        return this->p[this->n];
    }
    
    void operator=(const Vector &obj) {
        if(this->p != NULL) {
            delete[] this->p;
        }
        this->n = obj.n;
        this->capacity = obj.capacity;
        this->p = new T[this->capacity];
        memcpy(this->p, obj.p, this->n * sizeof(T));
    }
};

#endif
