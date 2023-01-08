/*
・TLEコードを改修。
・最小値の最大化、決め打ちにぶたん
・ちゃんと上界をmax(A)*N+Kって見積もって、初期化もO(N)でやったら通った。
　でも2.78秒らしいので多分ギリギリ。TL3秒なのかな。
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

class Solution {
public:
    long long maxPower(const vector<int> &stations, int R, int K) {
        vector<ll> A(ALL(stations));
        ll N = A.size();
        ll res = bisearch_max(0, 12000000000, [&](ll x) {
            BIT<ll> bit(A);
            ll use = 0;
            rep(i, N) {
                ll l = max(i - R, 0LL);
                ll r = min(i + R + 1, N);
                ll sm = bit.query(l, r);
                if (sm < x) {
                    ll need = x - sm;
                    bit.add(r - 1, need);
                    use += need;
                }
            }
            return use <= K;
        });
        return res;
    }
};

#ifdef __LOCAL
int main() {
    Solution sol;
    auto res = sol.maxPower({1, 2, 4, 5, 0}, 1, 2);
    print(res);
    return 0;
}
#endif
