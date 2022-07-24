/*
・きっちり自力AC！
・map,setをうまいこと使ってぐりぐりシミュると通る。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

class NumberContainers {
public:
    map<ll, set<ll>> dat;
    map<ll, ll> keys;
    NumberContainers() {}
    
    void change(int index, int number) {
        if (keys.count(index)) {
            dat[keys[index]].erase(index);
        }
        dat[number].insert(index);
        keys[index] = number;
    }
    
    int find(int number) {
        if (dat.count(number) and dat[number].size()) {
            return *dat[number].begin();
        } else {
            return -1;
        }
    }
};

#ifdef __LOCAL
    int main() {
        // Solution sol;
        // auto res = sol.funcName();
        // print(res);
        return 0;
    }
#endif
