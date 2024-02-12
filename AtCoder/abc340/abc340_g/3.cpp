/*
ライブラリ整備：Auxiliary Tree
・自分の手持ちはとても遅くて、速そうで使いやすそうなsuisenさんのを拝借。
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

#include "graph/AuxiliaryTree.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;
    A--;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vvi adj(N);
    rep(u, N) {
        adj[A[u]].eb(u);
    }
    AuxiliaryTree aux(nodes);
    mint ans = 0;
    // dp[u] := 頂点uを根とする部分木の通り数(色cではない孤立点は除く)
    vector<mint> dp(N, 1);
    rep(c, N) {
        if (adj[c].empty()) continue;
        ll r = aux.build(adj[c]);
        auto dfs = [&](auto &&f, ll u, ll prv) -> void {
            // sub:= uの親側を切った時、次数1になってしまう通り数
            mint sub = 0;
            for (auto v : aux[u]) {
                if (v == prv) continue;
                f(f, v, u);
                // vの部分木全通り + この部分木から何も使わないの1通り
                dp[u] *= dp[v] + 1;
                // この部分木vだけ使う(親側を切った時、次数1になってしまう)通り数
                sub += dp[v];
            }
            if (A[u] != c) {
                // 色cではない孤立点
                dp[u]--;
                // ここで親側を切って確定とする分を答えに足す
                // 親側を切った時、次数1になってしまう分を引く
                ans += dp[u] - sub;
            } else {
                // ここが色cなら普通になんでもOK
                ans += dp[u];
            }
        };
        dfs(dfs, r, -1);

        for (auto u : aux.get_vertices()) {
            dp[u] = 1;
        }
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
