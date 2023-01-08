/*
・TLEコードを改修。
・最小値の最大化、決め打ちにぶたん
・ちゃんと上界をmax(A)*N+Kって見積もって、初期化もO(N)でやったら通った。
　でも2.78秒らしいので多分ギリギリ。TL3秒なのかな。
・BITを毎回初期化しないで、操作列を残しておいて次回開始前に戻す、みたいにした。
　で、早々に無理なことが確定したら途中で不可なことをearly returnする。
　これだと1.40秒になった。
・決め打ちにぶたんのlogってだいたい重いので、
　logもう1個乗る時はこういう小技は入れるようにした方がいいかもしれない。
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
        BIT<ll> bit(A);
        vector<pll> ops;
        ll res = bisearch_max(0, 12000000000, [&](ll x) {
            for (auto [i, k] : ops) {
                bit.add(i, -k);
            }
            ops.clear();
            ll use = 0;
            rep(i, N) {
                ll l = max(i - R, 0LL);
                ll r = min(i + R + 1, N);
                ll sm = bit.query(l, r);
                if (sm < x) {
                    ll need = x - sm;
                    bit.add(r - 1, need);
                    ops.eb(r - 1, need);
                    use += need;
                }
                if (use > K) {
                    return false;
                }
            }
            return true;
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
