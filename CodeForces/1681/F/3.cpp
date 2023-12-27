/*
ライブラリ整備：オフラインダイコネ
・速いやつを仕入れたのでverifyを。問題なくAC。速度は2.09→1.68秒に。
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

#include "graph/OfflineDynamicConnectivity.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<vector<pii>> adj(N);
    OfflineDynamicConnectivity odc(N);
    rep(i, N - 1) {
        ll u, v, x;
        cin >> u >> v >> x;
        u--; v--; x--;
        adj[x].eb(u, v);
        odc.add_edge(u, v);
    }

    vector<int> ttoc(N * 4, -1);
    rep(c, N) {
        for (auto [u, v] : adj[c]) {
            odc.remove_edge(u, v);
        }
        ttoc[odc.query()] = c;
        for (auto [u, v] : adj[c]) {
            odc.add_edge(u, v);
        }
    }

    ll ans = 0;
    odc.solve([&](int t) {
        assert(ttoc[t] != -1);
        int c = ttoc[t];
        for (auto [u, v] : adj[c]) {
            ans += (ll)odc.uf.size(u) * odc.uf.size(v);
        }
    });
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
