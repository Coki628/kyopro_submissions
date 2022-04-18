/*
・きっちり自力AC！
・実務っぽい実装問題。あとことかこどふぉには絶対出なそうなので、ちょっと面白かった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

class ATM {
public:
    vector<ll> cnt = {0, 0, 0, 0, 0}, vals = {20, 50, 100, 200, 500};

    ATM() {}
    
    void deposit(vector<int> arg) {
        rep(i, 5) {
            cnt[i] += arg[i];
        }
    }
    
    vector<int> withdraw(int amount) {
        vector<int> res(5);
        auto tmp = cnt;
        rep(i, 4, -1, -1) {
            ll use = min(amount / vals[i], cnt[i]);
            amount -= use * vals[i];
            cnt[i] -= use;
            res[i] += use;
        }
        if (amount > 0) {
            cnt = tmp;
            return {-1};
        } else {
            return res;
        }
    }
};

/**
 * Your ATM object will be instantiated and called as such:
 * ATM* obj = new ATM();
 * obj->deposit(banknotesCount);
 * vector<int> param_2 = obj->withdraw(amount);
 */

#ifdef __LOCAL
    int main() {
        // Solution sol;
        // auto res = sol.funcName();
        // print(res);
        return 0;
    }
#endif
