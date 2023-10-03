/*
・bitDP
・M<=100でどう扱うかちょっと悩んだけど、なんてことはない、
　全状態で毎回M種類使って試せばOK。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> B(M);
    rep(i, M) {
        rep(j, N) {
            ll a;
            cin >> a;
            if (a) {
                B[i] |= 1LL << j;
            }
        }
    }

    vector<ll> dp(1LL << N, INF);
    dp[0] = 0;
    rep(bit, 1LL << N) {
        if (dp[bit] >= INF) continue;
        rep(i, M) {
            chmin(dp[bit | B[i]], dp[bit] + 1);
        }
    }
    ll ans = dp[(1LL << N) - 1] < INF ? dp[(1LL << N) - 1] : -1;
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
