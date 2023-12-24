/*
・きっちり自力AC！
・グリッド、期待値、UF
・期待値と言ってるけどようは赤マス1個緑マスに変えた時の連結状態が全通り見れればいい。
　なんかぱっと見辺削除が要りそうにも思えるけど要らない。
　1手先を試すだけなので、現状の連結状態から全部分かる。
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

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    ll N = H * W;
    UnionFind uf(N);
    rep(h, H) {
        rep(w, W) {
            if (h + 1 < H and grid[h][w] == '#' and grid[h + 1][w] == '#') {
                ll u = gridtoid(h, w, W);
                ll v = gridtoid(h + 1, w, W);
                uf.merge(u, v);
            }
            if (w + 1 < W and grid[h][w] == '#' and grid[h][w + 1] == '#') {
                ll u = gridtoid(h, w, W);
                ll v = gridtoid(h, w + 1, W);
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
    mint base = se.size();
    mint sm = 0, total = 0;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '.') {
                total++;
                set<ll> se;
                for (auto [dh, dw] : dir4) {
                    int nh = h + dh;
                    int nw = w + dw;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (grid[nh][nw] == '#') {
                        ll v = gridtoid(nh, nw, W);
                        se.insert(uf.find(v));
                    }
                }
                if (se.empty()) {
                    sm += base + 1;
                } else {
                    sm += base - (se.size() - 1);
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
