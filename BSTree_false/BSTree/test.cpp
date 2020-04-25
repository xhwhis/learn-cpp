#include <iostream>
#include "my_set.h"
using namespace std;

int main() {
    Set<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    cout << a[1] << endl;
    return 0;
}
