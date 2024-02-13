/*
参考：https://kntychance.hatenablog.jp/entry/2022/09/16/161858
ライブラリ整備：二重辺連結成分分解
・縮約後のグラフは木なので色々できる。
　今回はHLD*BITに突っ込んで、パスクエリでA,C間にBが存在するかチェックしてる。
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

#include "graph/TwoEdgeConnectedComponents.hpp"
#include "graph/HeavyLightDecomposition.hpp"

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

    TwoEdgeConnectedComponents tecc(nodes);
    HeavyLightDecomposition hld(tecc.get_nodes());
    ll K = tecc.size();
    BIT<ll> bit(K);
    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--, c--;
        bit.add(hld[tecc[b]], 1);
        ll cnt = hld.query(
            tecc[a],
            tecc[c],
            0LL,
            [&](ll a, ll b) { return bit.query(a, b); },
            [](ll a, ll b) { return a + b; }
        );
        if (cnt > 0) {
            print("OK");
        } else {
            print("NG");
        }
        bit.add(hld[tecc[b]], -1);
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
