/*
・後ろからDP、セグ木で遷移高速化
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, L, R;
    cin >> N >> L >> R;
    vector<ll> X(N);
    cin >> X;

    auto dp = get_segment_tree(N, [](ll a, ll b) { return min(a, b); }, INF);
    dp.update(N - 1, 0);
    rep(i, N - 2, -1, -1) {
        ll l = bisect_left(X, X[i] + L, i);
        ll r = bisect_left(X, X[i] + R + 1, i);
        dp.update(i, dp.query(l, r) + 1);
    }
    ll ans = dp[0];
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
