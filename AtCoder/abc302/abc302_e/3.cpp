/*
ライブラリ整備：オフラインダイコネ
・連結成分くらいはUF側に組み込んだけど、アドホックな何かが欲しい時用の仕様をダイコネ側に作った。
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

#include "graph/OfflineDynamicConnectivity.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<set<ll>> nodes(N);
    OfflineDynamicConnectivity odc(N);
    vector<ll> ttoq(Q * 3, -1);
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            nodes[u].insert(v);
            nodes[v].insert(u);
            odc.add_edge(u, v);
        } else {
            ll u;
            cin >> u;
            u--;
            for (auto v : nodes[u]) {
                nodes[v].erase(u);
                odc.remove_edge(u, v);
            }
            nodes[u].clear();
        }
        ttoq[odc.query()] = i;
    }
    vector<ll> ans(Q);
    int cnt = N;
    odc.solve([&](ll t) {
        assert(ttoq[t] != -1);
        ans[ttoq[t]] = cnt;
    }, [&](int u, int v) {
        if (odc.uf.size(u) == 1) cnt--;
        if (odc.uf.size(v) == 1) cnt--;
    }, [&](int u, int v) {
        if (odc.uf.size(u) == 1) cnt++;
        if (odc.uf.size(v) == 1) cnt++;
    });
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
