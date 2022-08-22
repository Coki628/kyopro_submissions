/*
・きっちり自力AC！
・dp[j][i] := pqrをjまで進めて、数列の位置iに到達できるか みたいなDPした。
　遷移先は累積和にぶたんで探した。
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
    auto pqr = LIST(3);
    auto A = LIST(N);

    Accumulate<ll> acc(A);
    auto dp = listnd(4, N+1, false);
    rep(i, N) {
        dp[0][i] = true;
    }
    rep(i, N) {
        rep(j, 3) {
            if (dp[j][i]) {
                ll k = bisearch_min(i, N+1, [&](ll r) {
                    return acc.query(i, r) >= pqr[j];
                });
                if (k <= N and acc.query(i, k) == pqr[j]) {
                    dp[j+1][k] = true;
                }
            }
        }
    }
    rep(i, N+1) {
        if (dp[3][i]) {
            Yes();
            return;
        }
    }
    No();
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
