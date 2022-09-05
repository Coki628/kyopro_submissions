/*
・きっちり自力AC！
・それぞれセグ木と累積和にして、左端固定右端にぶたん。
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
    int maximumRobots(vector<int>& tmp1, vector<int>& tmp2, long long M) {
        ll N = tmp1.size();
        vector<ll> A(N), B(N);
        rep(i, N) {
            A[i] = tmp1[i];
            B[i] = tmp2[i];
        }
        auto seg = get_segment_tree(A, [](ll a, ll b) { return max(a, b); }, 0LL);
        Accumulate<ll> acc(B);
        ll ans = 0;
        rep(l, N) {
            ll r = bisearch_max(l, N+1, [&](ll r) {
                return seg.query(l, r) + (r-l)*acc.query(l, r) <= M;
            });
            chmax(ans, r-l);
        }
        return ans;
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
