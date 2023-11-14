/*
・きっちり自力AC！
・貰うDP高速化、にぶたん
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
    ll N, W, L, R;
    cin >> N >> W >> L >> R;
    vector<ll> X(N);
    cin >> X;

    X.insert(X.begin(), 0);
    X.eb(W);
    N += 2;
    BIT<mint> dp(N);
    dp.add(0, 1);
    rep(i, 1, N) {
        ll r = X[i] - L + 1;
        ll l = X[i] - R;
        ll j = bisect_left(X, l);
        ll k = bisect_left(X, r);
        dp.add(i, dp.query(j, k));
    }
    mint ans = dp[N - 1];
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
