/*
・復元なし版。確かにこれだと簡潔だし、
　これが見えたなら青diffスレスレってのも頷けるか…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    vvi nodes(N);
    rep(i, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    vector<ll> W(N), A(N);
    cin >> W >> A;

    vector<pll> WI;
    rep(i, N) {
        WI.eb(W[i], i);
    }
    sort(ALL(WI));

    vector<ll> B(N);
    for (auto [_, u] : WI) {
        ll n = nodes[u].size();
        auto dp = listnd(n + 1, W[u], -INF);
        dp[0][0] = 0;
        rep(i, n) {
            ll v = nodes[u][i];
            rep(w, W[u]) {
                if (dp[i][w] == -INF) continue;
                chmax(dp[i + 1][w], dp[i][w]);
                if (w + W[v] < W[u]) {
                    chmax(dp[i + 1][w + W[v]], dp[i][w] + B[v]);
                }
            }
        }
        B[u] = 1 + max(dp[n]);
    }

    ll ans = 0;
    rep(i, N) {
        ans += A[i] * B[i];
    }
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
