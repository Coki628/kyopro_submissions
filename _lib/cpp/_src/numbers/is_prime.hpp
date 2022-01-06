#include "../macros.hpp"

// 素数判定：O(√num)
bool is_prime(ll num) {
    if (num < 2) {
        return false;
    }
    if (num == 2 or num == 3 or num == 5) {
        return true;
    }
    if (num%2 == 0 or num%3 == 0 or num%5 == 0) {
        return false;
    }
    // 疑似素数(2でも3でも割り切れない数字)で次々に割っていく
    int p = 7;
    int step = 4;
    int num_sqrt = sqrt(num);
    while (p <= num_sqrt) {
        if (num%p == 0) {
            return false;
        }
        p += step;
        step = 6-step;
    }
    return true;
}
