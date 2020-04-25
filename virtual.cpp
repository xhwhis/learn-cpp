#include <iostream>
#include <string>
using namespace std;

string rand_name(int n) {
    string name = "";
    for (int i = 0; i < n; i++) {
        name = name + (char)(rand() % 26 + 'A');
    }
    return name;
}

class Animal {
public:
    Animal(string name) : name(name) {}
    string get_name() {return this->name;}
    virtual void run() {
        cout << "I don't know how to run." << endl;
    }
    virtual void say() = 0;
    virtual ~Animal() {
        cout << "kill Animal" << endl;
    }
private:
    string name;
};

class Cat : public Animal {
public:
    Cat() : Animal("Cat " + rand_name(5)) {}
    void run() override {
        cout << "I can run with four legs." << endl;
    }
    void say() override {
        cout << "miao~miao~miao~" << endl;
    }
    ~Cat() {
        cout << "kill Cat" << endl;
    }
};

class Bat : public Animal {
public:
    Bat() : Animal("Bat " + rand_name(5)) {}
    void run() override {
        cout << "I can fly." << endl;
    }
    void say() override {
        cout << "zzz~zzz~zzz~" << endl;
    }
    ~Bat() {
        cout << "kill Bat" << endl;
    }
};

int main() {
    Cat cat_a;
    Bat bat_a;
    cout << cat_a.get_name() << endl;
    cat_a.run();
    cout << bat_a.get_name() << endl;
    bat_a.run();
    Animal **p = new Animal*[10];
    for (int i = 0; i < 10; i++) {
        if (rand() % 2) {
            p[i] = new Cat();
        } else {
            p[i] = new Bat();
        }
    }
    for (int i = 0; i < 10; i++) {
        cout << p[i]->get_name() << endl;
        p[i]->run();
        p[i]->say();
    }
    for (int i = 0; i < 10; i++) {
        delete p[i];
    }
    delete[] p;
    return 0;
}
