/*
・きっちり自力AC！
・グリッド、UF
・とりあえず同じ色の領域は連結成分にして、連結成分毎に周囲を見て、
　周りにある各連結成分を色毎に集計して、自分の成分数と合わせる、みたいにした。
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

void solve() {
    ll H, W;
    cin >> H >> W;
    auto grid = listnd(H, W, 0LL);
    rep(h, H) {
        rep(w, W) {
            cin >> grid[h][w];
        }
    }

    ll N = H * W;
    UnionFind uf(N);
    rep(h, H) {
        rep(w, W) {
            ll u = gridtoid(h, w, W);
            for (auto [dh, dw] : dir4) {
                ll nh = h + dh;
                ll nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                ll v = gridtoid(nh, nw, W);
                if (grid[h][w] == grid[nh][nw]) {
                    uf.merge(u, v);
                }
            }
        }
    }
    vvi nodes(N);
    rep(h, H) {
        rep(w, W) {
            ll u = gridtoid(h, w, W);
            for (auto [dh, dw] : dir4) {
                ll nh = h + dh;
                ll nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                ll v = gridtoid(nh, nw, W);
                if (grid[h][w] != grid[nh][nw]) {
                    nodes[uf.find(u)].eb(uf.find(v));
                    nodes[uf.find(v)].eb(uf.find(u));
                }
            }
        }
    }
    ll ans = 0;
    for (auto r : uf.get_roots()) {
        UNIQUE(nodes[r]);
        chmax(ans, uf.size(r));
        map<ll, ll> C;
        for (auto v : nodes[r]) {
            auto [h, w] = idtogrid(v, W);
            C[grid[h][w]] += uf.size(v);
        }
        for (auto [k, val] : C) {
            chmax(ans, uf.size(r) + val);
        }
    }
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
