#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    long long a = 1234567890;
    auto b = a;
    cout << sizeof(b) << endl;
    map<string, int> arr;
    arr["hello"] = 123;
    arr["haizei"] = 456;
    arr["China"] = 789;
    for (auto iter = arr.begin(); iter != arr.end(); iter++) {
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}
