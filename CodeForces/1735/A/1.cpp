/*
・自力AC！
・二分探索
・にぶたんした。まあ正攻法だと割り算するやつだけど、
　この辺で理詰め頑張ると疲れるし考慮漏れあった時もたつくから。。
　(とはいえにぶたんも境界ミスったりするので決して確実ではない…。)
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

void solve() {
    ll N;
    cin >> N;

    ll res = bisearch_max(0, N, [&](ll x) {
        ll cur = 0;
        ll need1 = 1;
        cur += need1 + 1;
        ll need2 = need1 + x;
        cur += need2 + 1;
        ll need3 = need2 + x;
        cur += need3 + 1;
        return cur <= N;
    });
    print(res);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
