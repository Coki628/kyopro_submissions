/*
・きっちり自力AC！
・一般マッチング
・bitDP
・ビット2つずつ埋めてく感じでbitDPする。
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
    auto G = listnd(N, N, INF);
    rep(u, N) {
        rep(v, u + 1, N) {
            ll c;
            cin >> c;
            G[u][v] = c;
            G[v][u] = c;
        }
    }

    vector<ll> dp(1LL << N, -INF);
    dp[0] = 0;
    rep(bit, 1LL << N) {
        if (dp[bit] == -INF) {
            continue;
        }
        rep(u, N) {
            rep(v, u + 1, N) {
                if (bit >> u & 1 or bit >> v & 1) {
                    continue;
                }
                chmax(dp[bit | (1LL << u) | (1LL << v)], dp[bit] + G[u][v]);
            }
        }
    }
    ll ans = max(dp);
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
