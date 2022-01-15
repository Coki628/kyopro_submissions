/*
・きっちり自力AC！
・最小全域木、HLD、セグ木
・past202004_oと本質はほぼ同じでいける。こっちのがちょっと弱体化版。
・MSTに新しい辺を1つ追加する時、そのサイクルに含まれる一番重い辺がMSTから外れる。
　これを判定すればいい。
・なんか公式解はクエリ先読みでクエリの辺も混ぜてソートみたいな賢い解法をやってた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/graph/HeavyLightDecomposition.hpp"

void solve() {
    ll N, M, Q;
    cin >> N >> M >> Q;
    ll a, b, c;
    vector<tuple<ll, ll, ll>> edges, mst;
    rep(_, 0, M) {
        cin >> a >> b >> c;
        a--; b--;
        edges.pb({c, a, b});
    }
    sort(edges.begin(), edges.end());

    UnionFind uf(N);
    vvi nodes(N);
    set<pll> used;
    ll mncost = 0;
    for (auto [c, a, b] : edges) {
        if (!uf.same(a, b)) {
            uf.merge(a, b);
            nodes[a].pb(b);
            nodes[b].pb(a);
            mst.pb({a, b, c});
            used.insert({a, b});
            used.insert({b, a});
            mncost += c;
        }
    }

    auto seg = get_segment_tree(N, [](ll a, ll b) -> ll { return max(a, b); }, -INF);
    HeavyLightDecomposition hld(nodes);
    hld.build();

    ll u, v;
    for (auto edge : mst) {
        tie(u, v, c) = edge;
        // a == b の時は更新処理されないようにする
        hld.add(u, v, [&](ll a, ll b) { if (a != b) seg.update(a, c); }, true);
    }

    rep(_, Q) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        // [u,v]パス上の辺から最大コストを取得
        ll mx = hld.query(
            u, v, -INF,
            [&](ll a, ll b) { return seg.query(a, b); },
            [](ll a, ll b) { return max(a, b); }, true
        );
        if (w < mx) Yes();
        else No();
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
