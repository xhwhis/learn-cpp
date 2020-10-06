#include <iostream>
#include <ctime>
using namespace std;

class ICar {
public:
    class IFactor {
    public:
        virtual ICar *create() = 0;
    };
    virtual void run() = 0;
protected:
    ICar() {}
    ~ICar() {}
};

class benzCar : public ICar {
private:
    benzCar() {}
public:
    class Factory : public ICar::IFactor {
    public:
        virtual ICar *create() {
            return new benzCar();
        }
    };
    virtual void run() {
        cout << "benz run" << endl;
    }
};

class bmwCar : public ICar {
private:
    bmwCar() {}
public:
    class Factory : public ICar::IFactor {
    public:
        virtual ICar *create() {
            return new bmwCar();
        }
    };
    virtual void run() {
        cout << "bmw run" << endl;
    }
};

class audiCar : public ICar {
    audiCar() {}
public:
    class Factory : public ICar::IFactor {
    public:
        virtual ICar *create() {
            return new audiCar();
        }
    };
    virtual void run() {
        cout << "audi run" << endl;
    }
};

ICar::IFactor *fac[3] = {new benzCar::Factory(), new bmwCar::Factory(), new audiCar::Factory()};

int main() {
    srand(time(0));
    ICar *cars[10];
    for (int i = 0; i < 10; i++) {
        cars[i] = fac[rand() % 3]->create();
    }
    for (int i = 0; i < 10; i++) {
        cars[i]->run();
    }
    return 0;
}
