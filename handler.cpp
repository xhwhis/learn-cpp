#include <iostream>
#include <ctime>
using namespace std;

class ICar {
public:
    class IFactory {
    public :
        virtual ICar *crearte() = 0;
    };
    class IHandler {
    public :
        IHandler() : next(nullptr) {}
        virtual bool is_valid(int x) = 0;
        virtual ICar *do_it() = 0;
        IHandler *next;
    };
    virtual void run() = 0;
protected:
    ICar() {}
    ~ICar() {}
};

class benzCar : public ICar {
    benzCar() {}
public:
    class Facory : public ICar::IFactory, public ICar::IHandler {
    public:
        virtual ICar *crearte() {
            return new benzCar();
        }
        virtual bool is_valid(int x) {
            return x == 0;
        }
        virtual ICar *do_it() {
            return this->crearte();
        }
    };
    virtual void run() {
        cout << "benz run" << endl;
    }
};

class bmwCar : public ICar {
    bmwCar() {}
public:
    class Facory : public ICar::IFactory, public ICar::IHandler {
    public:
        virtual ICar *crearte() {
            return new bmwCar();
        }
        virtual bool is_valid(int x) {
            return x == 1;
        }
        virtual ICar *do_it() {
            return this->crearte();
        }
    };
    virtual void run() {
        cout << "bmw run" << endl;
    }
};

class audiCar : public ICar {
    audiCar() {}
public :
    class Facory : public ICar::IFactory, public IHandler {
    public :
        virtual ICar *crearte() {
            return new audiCar();
        }
        virtual bool is_valid(int x) {
            return x == 2;
        }
        virtual ICar *do_it() {
            return this->crearte();
        }
    };
    virtual void run() {
        cout << "audi run" << endl;
    }
};

class ChainMaster {
public :
    static ICar::IHandler *getInstance() {
        if (head == nullptr) {
            buildChain();
        }
        return head;
    }
private :
    static ICar::IHandler *head;
    static void buildChain() {
        head = new bmwCar::Facory();
        head->next = new audiCar::Facory();
        head->next->next = new benzCar::Facory();
        return ;
    }
};

ICar::IHandler *ChainMaster::head = nullptr;

int main() {
    srand(time(0));
    ICar *cars[10];
    for (int i = 0; i < 10; i++) {
        int req = rand() % 3;
        for (auto p = ChainMaster::getInstance(); p; p = p->next) {
            if (p->is_valid(req)) {
                cars[i] = p->do_it();
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        cars[i]->run();
    }
    return 0;
}
