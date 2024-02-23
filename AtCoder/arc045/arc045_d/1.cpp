/*
参考：https://kntychance.hatenablog.jp/entry/2022/09/16/161858#%E4%BE%8B%E9%A1%8C-1
ライブラリ整備：Block Cut Tree
・「偶数個の連結成分ならどうとでもペアにできる」
　ってのは思いつかない気がするけど、その先は場合分けとBCTと木DP。
・あとこれが通るってことは多分、元グラフ構築時に雑に二重辺作っても
　BCTの構築はちゃんと動くんだと思う。いいね。
　(サイクルにする際に、2個しか要素ない所まで2回つないでいるので)
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

#include "graph/BlockCutTree.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi adjx(N * 2 + 1), adjy(N * 2 + 1);
    rep(i, N * 2 + 1) {
        ll x, y;
        cin >> x >> y;
        x--, y--;
        adjx[x].eb(i);
        adjy[y].eb(i);
    }

    // x,y座標が同じ所を全部つないでサイクルにしておく
    vvi nodes(N * 2 + 1);
    UnionFind uf(N * 2 + 1);
    rep(x, N * 2 + 1) {
        ll n = adjx[x].size();
        rep(i, n) {
            ll u = adjx[x][i];
            ll v = adjx[x][(i + 1) % n];
            nodes[u].eb(v);
            nodes[v].eb(u);
            uf.merge(u, v);
        }
    }
    rep(y, N * 2 + 1) {
        ll n = adjy[y].size();
        rep(i, n) {
            ll u = adjy[y][i];
            ll v = adjy[y][(i + 1) % n];
            nodes[u].eb(v);
            nodes[v].eb(u);
            uf.merge(u, v);
        }
    }
    BlockCutTree bct(nodes);
    ll K = bct.size();
    ll oddcnt = 0, r = -1, szsm = 0;
    for (auto v : uf.get_roots()) {
        if (uf.size(v) % 2 == 1) {
            oddcnt++;
            // 唯一の奇数個連結成分を覚えておく
            r = bct.id(v);
            szsm = uf.size(v);
        }
    }
    assert(oddcnt != 0);
    vector<string> ans(N * 2 + 1, "NG");
    // 要素奇数個の連結成分が複数あったらどうやっても無理
    if (oddcnt > 1) {
        print(ans, '\n');
        return;
    }

    // 以下、唯一の奇数個連結成分に注目して木DP
    vector<ll> sz(K);
    auto groups = bct.get_groups();
    auto nodes2 = bct.get_nodes();
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        sz[u] = bct.size(u);
        for (auto v : nodes2[u]) {
            if (v == prv) continue;
            f(f, v, u);
            sz[u] += sz[v];
        }
        bool ok = true;
        if (bct.is_articulation(u)) {
            // 関節点は、外した時周りが全部偶数個になってればOK
            ok = (szsm - sz[u]) % 2 == 0;
            if (ok) {
                for (auto v : nodes2[u]) {
                    if (v == prv) continue;
                    if (sz[v] % 2 != 0) {
                        ok = false;
                        break;
                    }
                }
            }
        }
        if (ok) {
            for (auto x : groups[u]) {
                ans[x] = "OK";
            }
        }
    };
    dfs(dfs, r, -1);
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
