/*
・なんとか自力AC！
・最小値の最大化、決め打ちにぶたん
・区間和をBITでサボったら無慈悲なTLEが取れないので泣きながら尺取りみたいにして終了1分前AC。
　なんかりとこ意外とこういうlog殺し多い気がする。
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
    long long maxPower(const vector<int> &A, int R, int K) {
        ll N = A.size();
        ll res = bisearch_max(0, 100000000000000, [&](ll x) {
            auto vec = A;
            ll cur = 0;
            rep(i, min((ll)R, N)) {
                cur += vec[i];
            }
            ll use = 0;
            rep(i, N) {
                ll l = i - R;
                ll r = i + R;
                if (l > 0) {
                    cur -= vec[l - 1];
                }
                if (r < N) {
                    cur += vec[r];
                }
                if (cur < x) {
                    ll need = x - cur;
                    vec[min(r, N - 1)] += need;
                    use += need;
                    cur += need;
                }
                assert(cur >= x);
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
