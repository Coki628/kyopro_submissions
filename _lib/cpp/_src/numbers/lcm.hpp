#include "../macros.hpp"
#include "gcd.hpp"

// 除算を前に出してオーバーフローを防ぐ
ll lcm(ll x, ll y) { return x/gcd(x, y)*y; }

template<typename T>
T lcm(const vector<T> &A) {
    T res = 1;
    for (auto a : A) res = lcm(res, a);
    return res;
}
