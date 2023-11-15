/*
・きっちり自力AC！
・区切るDP、コスト前計算
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
    ll N, M, K;
    cin >> N >> M >> K;
    vector<pii> edges;
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        edges.eb(a, b);
    }

    auto score = listnd(N, N + 1, 0);
    rep(l, N) {
        rep(r, l + 1, N + 1) {
            ll cnt = 0;
            for (auto [a, b] : edges) {
                if (l <= a and b < r) {
                    cnt++;
                }
            }
            score[l][r] = cnt;
        }
    }

    auto dp = listnd(N + 1, K + 1, -INF);
    dp[0][0] = 0;
    rep(r, 1, N + 1) {
        rep(j, K) {
            rep(l, r) {
                chmax(dp[r][j + 1], dp[l][j] + score[l][r]);
            }
        }
    }
    ll ans = dp[N][K];
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
