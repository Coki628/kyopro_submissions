/*
ライブラリ整備：Block Cut Tree
・この問題は題意が頂点削除なので、BCTのが簡潔に条件書けるかもと思いやってみる。
　すると孤立点の扱いが意外と気をつけないといけなくて、さくっとは終わらなかった。
　普通に縮約グラフで孤立点も見ようとしたら、
　元グラフで関節点のない頂点2個の連結成分とかが、
　縮約後には孤立点になっていて、これを元グラフでも孤立点だと誤判定したりした。
　分かってみればそれはそうなのだが、整理できてよかった。
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

#include "graph/BlockCutTree.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    ll N = H * W;
    vvi nodes(N);
    UnionFind uf(N);
    rep(h, H) {
        rep(w, W) {
            if (h + 1 < H and grid[h][w] == '#' and grid[h + 1][w] == '#') {
                ll u = gridtoid(h, w, W);
                ll v = gridtoid(h + 1, w, W);
                nodes[u].eb(v);
                nodes[v].eb(u);
                uf.merge(u, v);
            }
            if (w + 1 < W and grid[h][w] == '#' and grid[h][w + 1] == '#') {
                ll u = gridtoid(h, w, W);
                ll v = gridtoid(h, w + 1, W);
                nodes[u].eb(v);
                nodes[v].eb(u);
                uf.merge(u, v);
            }
        }
    }
set<ll> se;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '#') {
                ll u = gridtoid(h, w, W);
                se.insert(uf.find(u));
            }
        }
    }
    ll compcnt = se.size();
    BlockCutTree bct(nodes);
    auto nodes2 = bct.get_nodes();
    auto groups = bct.get_groups();
    mint sm = 0, total = 0;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '#') {
                total++;
                ll u = gridtoid(h, w, W);
                ll k = bct.id(u);
                // 関節点
                if (bct.is_articulation(k)) {
                    sm += compcnt + (int)bct[k].size() - 1;
                // (元グラフ上で)孤立点
                } else if (nodes2[k].size() == 0 and groups[k].size() == 1) {
                    sm += compcnt - 1;
                } else {
                    sm += compcnt;
                }
            }
        }
    }
    mint ans = sm / total;
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
