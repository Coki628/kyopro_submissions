/*
参考：https://twitter.com/SSRS_cp/status/1733548698637111454
・自力ならず。でも学びがあっていい感じだった。
・木グラフ、クエリ、最遠点、頂点削除
・クエリ先読み、DFS、遅延セグ木、HLD、部分木クエリ
・実は木の頂点間距離は、遅延セグ木*部分木クエリに乗せて
　頂点移動時に適切にコストをスライドさせる感じにすると、
　任意のものが求まるという知見を得た。
　そして今回は頂点削除もあるが、これも部分木クエリで
　適切に各頂点を無効化して状態戻し、とやれば再現できる。
　これができると、後はよくあるクエリ先読みをしておいて、
　DFSで走査しながら各頂点毎にクエリを処理、とできる。
　この手の任意の根で最遠点求める感じやつは
　全方位に乗せるしかないと思ってたけど、
　遅延セグ木とDFSでできるんだねー。やれることの幅広がりそう。
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

#include "graph/HeavyLightDecomposition.hpp"
#include "datastructure/LazySegmentTree.hpp"

// 区間加算・区間最大値取得
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = -INF;
const ll E = 0;

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vvi nodes(N);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    // クエリ先読み
    vvl A(Q), qs(N);
    rep(i, Q) {
        ll x, k;
        cin >> x >> k;
        x--;
        qs[x].eb(i);
        A[i].resize(k);
        cin >> A[i];
        A[i]--;
    }

    HeavyLightDecomposition hld(nodes);
    auto seg = get_lazy_segment_tree(N, f, g, h, T, E);
    // 初期値は根からの距離で
    rep(u, N) {
        seg.set(hld[u], hld.dep[u]);
    }
    seg.build();

    vector<ll> ans(Q);
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        for (auto i : qs[u]) {
            // 頂点a以降を無効な値にしておく
            for (auto a : A[i]) {
                ll lca = hld.lca(u, a);
                // aがuの祖先か
                if (lca == a) {
                    ll nxa = hld.next(a, u);
                    // nxaより祖先側を全て無効化
                    seg.update(0, N, -MOD);
                    seg.update(hld.in[nxa], hld.out[nxa], MOD);
                } else {
                    // uの祖先以外は部分木を無効化でOK
                    seg.update(hld.in[a], hld.out[a], -MOD);
                }
            }
            ans[i] = seg.all();
            // 状態戻し
            for (auto a : A[i]) {
                ll lca = hld.lca(u, a);
                if (lca == a) {
                    ll nxa = hld.next(a, u);
                    seg.update(0, N, MOD);
                    seg.update(hld.in[nxa], hld.out[nxa], -MOD);
                } else {
                    seg.update(hld.in[a], hld.out[a], MOD);
                }
            }
        }
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            // vから見た距離に更新
            seg.update(0, N, 1);
            seg.update(hld.in[v], hld.out[v], -2);
            f(f, v, u);
            // 状態戻し
            seg.update(0, N, -1);
            seg.update(hld.in[v], hld.out[v], 2);
        }
    };
    dfs(dfs, 0, -1);
    print(ans, "\n");
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
