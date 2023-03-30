/*
・自力ならず。。悔しいなーこれは。
・DFS、UF、HLD、パスの取得、グラフの縮約
・自力で考えた方針でだいたい合ってたけど、WAが出てたのは使う隣接リスト間違えてる箇所があって、
　TLEはパスの取得を高速にできるようにして、辺を陽にマージしてるのを消したら通った。
　でも辺を陽にマージしてるのはマージテクで高速化してるから問題ないはずで、
　よくよく確認したら、連結済の成分でも再度マージ処理しちゃってた。そりゃダメだわ…。
・パスの高速取得にはHLDを使った。逆辺も張ったグラフを作ると、
　これは頂点0を根とした根付き木なので、HLDに乗る。
　これでパスはLCAまでの1本道なので同じ連結成分になるまで遡ればいい。
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

#include "graph/HeavyLightDecomposition.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> P(N - 1);
    cin >> P;
    P--;
    vvi nodes(N), nodes2(N);
    rep(i, N - 1) {
        nodes[P[i]].eb(i + 1);
        nodes2[P[i]].eb(i + 1);
        nodes2[i + 1].eb(P[i]);
    }

    HeavyLightDecomposition hld(nodes2);

    vector<ll> mni(N, INF);
    auto dfs = [&](auto &&f, ll u) {
        if (mni[u] < INF) return;
        mni[u] = u;
        for (auto v : nodes[u]) {
            f(f, v);
            chmin(mni[u], mni[v]);
        }
    };
    rep(i, N) {
        dfs(dfs, i);
    }

    UnionFind uf(N);
    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            if (not uf.same(u, v)) {
                ll ru = uf.find(u);
                ll rv = uf.find(v);
                vector<ll> paths;
                ll lca = hld.lca(u, v);
                if (lca == u) {
                    ll cur = v;
                    ll rcur = uf.find(cur);
                    while (rcur != ru) {
                        paths.eb(rcur);
                        cur = hld.la(cur, 1);
                        rcur = uf.find(cur);
                    }
                } else if (lca == v) {
                    ll cur = u;
                    ll rcur = uf.find(cur);
                    while (rcur != rv) {
                        paths.eb(rcur);
                        cur = hld.la(cur, 1);
                        rcur = uf.find(cur);
                    }
                } else {
                    assert(0);
                }

                for (auto ru : paths) {
                    ru = uf.find(ru);
                    rv = uf.find(rv);
                    ll r = uf.merge(ru, rv);
                    if (r != -1) {
                        mni[r] = min(mni[ru], mni[rv]);
                    }
                }
            }
        } else {
            ll x;
            cin >> x;
            x--;
            ll rx = uf.find(x);
            print(mni[rx] + 1);
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
