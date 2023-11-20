/*
・なんとか自力AC！終了後だけどね。
・順列、Mo*HLD*BIT、部分木クエリ
・題意に合うかどうかの判定は、部分木クエリができれば1点更新と区間和取得にできる。
　これならHLDのパスクエリでついてたlogが外れるので、通るかもと思ってやってみると無事AC。
　0.64秒くらい。√も乗ってるのに、さすがにBIT単体のlogだとlog無いみたいに速い。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

#include "graph/HeavyLightDecomposition.hpp"
#include "datastructure/Mo.hpp"

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<pii> edges;
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        edges.eb(u, v);
    }
    vector<int> P(N);
    cin >> P;
    P--;

    vector<int> rev(N);
    rep(i, N) {
        rev[P[i]] = i;
    }
    vvi nodes(N);
    for (auto [u, v] : edges) {
        nodes[rev[u]].eb(rev[v]);
        nodes[rev[v]].eb(rev[u]);
    }
    HeavyLightDecomposition hld(nodes, rev[0]);
    Mo mo(N);
    BIT<int> bit(N);
    vector<int> X(Q);
    rep(i, Q) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, x--;
        mo.add(l, r);
        X[i] = x;
    }
    auto add = [&](int u) -> void {
        bit.add(hld.in[u], 1);
    };
    auto erase = [&](int u) -> void {
        bit.add(hld.in[u], -1);
    };
    vector<string> ans(Q);
    auto out = [&](int i) -> void {
        int u = rev[X[i]];
        if (bit.query(hld.in[u], hld.out[u]) > 0) {
            ans[i] = "YES";
        } else {
            ans[i] = "NO";
        }
    };
    mo.build(add, erase, out);
    print(ans, '\n');
    print();
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
