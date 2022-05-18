/*
・部分点1と2。
・部分点1は毎回愚直にBFS回せばOK。
　部分点2は同じ州をまとめて1つの頂点とみなしたグラフで、
　直接繋がってる辺があるかを判定できればOK。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll N, M, K;
    cin >> N >> M >> K;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    auto S = LIST(N);
    rep(i, N) S[i]--;

    vector<set<ll>> nodes2(K);
    rep(u, N) {
        for (auto v : nodes[u]) {
            nodes2[S[u]].insert(S[v]);
        }
    }

    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll a, b;
        cin >> a >> b;
        a--; b--;

        if (N <= 1000 and M <= 1000 and Q <= 1000) {
            vector<ll> res(N, INF);
            queue<int> que;
            que.push(a);
            res[a] = 0;
            while (!que.empty()) {
                int u = que.front(); que.pop();
                for (auto v: nodes[u]) {
                    if (S[v] != S[a] and S[v] != S[b]) continue;
                    if (chmin(res[v], res[u]+1)) {
                        que.push(v);
                    }
                }
            }
            ll ans = res[b] < INF;
            print(ans);
        } else {
            ll ans = nodes2[S[a]].count(S[b]);
            print(ans);
        }
    }
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
