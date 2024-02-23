/*
ライブラリ整備：Low Link
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

#include "graph/LowLink.hpp"

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
    LowLink lowlink(nodes);

    mint sm = 0, total = 0;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '#') {
                ll u = gridtoid(h, w, W);
                total++;
                ll ecnt = 0, bcnt = 0;
                for (auto [dh, dw] : dir4) {
                    int nh = h + dh;
                    int nw = w + dw;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (grid[nh][nw] == '#') {
                        ecnt++;
                        ll v = gridtoid(nh, nw, W);
                        if (lowlink.is_bridge(u, v)) {
                            bcnt++;
                        }
                    }
                }
                assert(bcnt != ecnt - 1);
                if (ecnt == bcnt) {
                    sm += compcnt + bcnt - 1;
                // 橋がないのに連結が壊れる → 2辺ずつ同じ成分にあって橋がないケース
                } else if (bcnt == 0 and lowlink.is_articulation(u)) {
                    assert(ecnt == 4);
                    sm += compcnt + 1;
                } else {
                    sm += compcnt + bcnt;
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
