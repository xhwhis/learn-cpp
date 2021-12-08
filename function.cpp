#include <iostream>
#include <functional>

using namespace std;

inline function<int()> squares() {
    int x = 0;
    return [&]() -> int {
        x++;
        return x * x;
    };
};

int main() {
    auto func = squares();
    cout << func() << endl;
    cout << func() << endl;
    cout << func() << endl;
    cout << func() << endl;
}
