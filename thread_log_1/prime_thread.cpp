#include <iostream>
#include <thread>
#include "thread_pool.h"
using namespace std;

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

void prime_cnt(int l, int r, int &ans) {
    int cnt = 0;
    for (int i = l; i <= r; i++) {
        cnt += is_prime(i);
    }
    __sync_fetch_and_add(&ans, cnt);
    return ;
}

int main() {
    int cnt = 0;
    haizei::thread_pool tp(5);
    tp.start();
    for (int i = 1; i <= 10; i++) {
        tp.add_one_task(prime_cnt, (i - 1) * 100000 + 1, i * 100000, ref(cnt));
    }
    tp.stop_until_empty();
    cout << cnt << endl;
    return 0;
}
