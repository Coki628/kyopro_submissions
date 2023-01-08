/*
・きっちり自力AC。
・指示通り作る。直前の値と連続回数を保持すればOK。
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

class DataStream {
    int value, k;
    int cur = -1, cnt = 0;
public:
    DataStream(int value, int k) : value(value), k(k) {}

    bool consec(int num) {
        if (cur == num) {
            cnt++;
        } else {
            cur = num;
            cnt = 1;
        }
        if (cnt >= k and cur == value) {
            return true;
        } else {
            return false;
        }
    }
};

/**
 * Your DataStream object will be instantiated and called as such:
 * DataStream* obj = new DataStream(value, k);
 * bool param_1 = obj->consec(num);
 */

#ifdef __LOCAL
int main() {
    // Solution sol;
    // auto res = sol.funcName();
    // print(res);
    return 0;
}
#endif
