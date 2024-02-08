/*
・なんとか自力AC！やったね。
・一般グラフ無向重み付き、サイクル、最小化、パス復元
・UF、MST、HLD*最小値セグ木、超頂点
・とりあえずMSTを構築、余った辺を繋ごうとすれば、
　そこで作られるサイクルのパスが取得できて、重みの最小値も取れる。
　これはHLDとセグ木でやる。一番小さい値が取れたパスを復元すれば答え。
　最小値の辺が、うまいことサイクルに含まれなくなってしまう
　パターンもあるんじゃないか、と思ったけど、
　他にいい案も出ないし、小さい辺はMSTになるべく入っているはずだし、
　作れるサイクルがあるなら多分そこも通るだろう、と雑に考えて実装、無事AC。
　グラフが連結とは限らないことで最後に詰まりかけたが、
　超頂点で連結成分全体を繋ぐことで事なきを得た。
・TL見てた感じ、全域木を大きい方から繋いでも良かったみたいなので、
　結局どんな全域木でもうまいことやれるのかもしれない。
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

#include "graph/HeavyLightDecomposition.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<array<ll, 3>> edges;
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        edges.pb({c, u, v});
    }

    sort(ALL(edges));
    UnionFind uf(N);
    vvi nodes(N + 1);
    vector<pii> edges2;
    vector<array<ll, 3>> edges3;
    map<pii, ll> mp;
    for (auto [c, u, v] : edges) {
        if (not uf.same(u, v)) {
            uf.merge(u, v);
            nodes[u].eb(v);
            nodes[v].eb(u);
            mp[{u, v}] = c;
            mp[{v, u}] = c;
            edges2.eb(u, v);
        } else {
            edges3.pb({u, v, c});
        }
    }
    // 超頂点でグラフ全体を連結にしておく
    for (auto r : uf.get_roots()) {
        nodes[r].eb(N);
        nodes[N].eb(r);
        mp[{r, N}] = MOD;
        mp[{N, r}] = MOD;
        edges2.eb(r, N);
    }

    HeavyLightDecomposition hld(nodes);
    auto seg = get_segment_tree(N, [](ll a, ll b) { return min(a, b); }, INF);
    for (auto [u, v] : edges2) {
        if (hld.dep[u] < hld.dep[v]) {
            seg.set(hld[v], mp[{u, v}]);
        } else {
            seg.set(hld[u], mp[{u, v}]);
        }
    }
    seg.build();

    ll mn = INF;
    pii edge;
    for (auto [u, v, c] : edges3) {
        ll res = hld.query(u, v, INF, [&](ll a, ll b) { return seg.query(a, b); }, [](ll a, ll b) { return min(a, b); }, true);
        chmin(res, c);
        if (chmin(mn, res)) {
            edge = {u, v};
        }
    }
    // パス復元
    auto [u, v] = edge;
    vector<ll> ans;
    ll cur = u;
    ll lca = hld.lca(u, v);
    while (cur != lca) {
        ans.eb(cur);
        cur = hld.la(cur, 1);
    }
    while (cur != v) {
        ans.eb(cur);
        cur = hld.next(cur, v, 1);
    }
    ans.eb(cur);
    cout << mn << ' ';
    print(ans.size());
    ans++;
    print(ans);
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
