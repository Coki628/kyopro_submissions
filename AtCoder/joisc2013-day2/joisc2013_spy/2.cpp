/*
・JOI埋め
・自力AC！やったね。
・前から木DP、bitset高速化
・非想定っぽいけど通せたので勝ち。M側をbitsetに乗せると、
　ループはN側だけになり、Nのi毎に数えるのもpopcountでよくなる。
　部分木を含めた各ビットの状態の作り方については、
　M個の各r,sについてまず影響の根となる頂点を更新しておいて、
　DFSで木DPを親側から更新してく感じにする。これで部分木の頂点全てに情報が届く。
　50万ビットのマージを2000回やるのは間に合うのか自信なかったけど、無事AC0.35秒。
　なにげにメモリが256MB制限だから248MBで結構ギリギリだったな…。
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
    ll N, M;
    cin >> N >> M;
    vvi nodes1(N), nodes2(N);
    ll r1 = -1, r2 = -1;
    rep(i, N) {
        ll p, q;
        cin >> p >> q;
        p-- ; q--;
        if (p == -1) {
            r1 = i;
        } else {
            nodes1[p].eb(i);
        }
        if (q == -1) {
            r2 = i;
        } else {
            nodes2[q].eb(i);
        }
    }

    vector<bitset<500000>> dp1(N), dp2(N);
    rep(i, M) {
        ll r, s;
        cin >> r >> s;
        r--; s--;
        dp1[r].set(i);
        dp2[s].set(i);
    }
    auto dfs = [&](auto&& f, ll u, const vvi& nodes, vector<bitset<500000>>& dp) -> void {
        for (auto v : nodes[u]) {
            dp[v] |= dp[u];
            f(f, v, nodes, dp);
        }
    };
    dfs(dfs, r1, nodes1, dp1);
    dfs(dfs, r2, nodes2, dp2);

    vector<ll> ans(N);
    rep(u, N) {
        ans[u] = (dp1[u]&dp2[u]).count();
    }
    print(ans, '\n');
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
