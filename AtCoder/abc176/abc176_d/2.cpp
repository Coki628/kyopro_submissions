/*
・dojo set_d_3_1
・きっちり自力AC！
・グリッド、辺を工夫
・これはまあ、当時もちゃんと手早く通してたしな。
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

#include "../../../_lib/cpp/_src/graph/_dijkstra.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    ll sh, sw, th, tw;
    cin >> sh >> sw >> th >> tw;
    sh--; sw--; th--; tw--;
    vector<string> grid(H);
    rep(i, H) {
        cin >> grid[i];
    }

    ll N = H*W;
    vvpll nodes(N);
    rep(h, H) {
        rep(w, W) {
            ll u = gridtoid(h, w, W);
            for (auto [dh, dw] : dir4) {
                int nh = h+dh;
                int nw = w+dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                if (grid[nh][nw] == '#') continue;
                ll v = gridtoid(nh, nw, W);
                nodes[u].eb(v, 0);
            }
            rep(dh, -2, 3) {
                rep(dw, -2, 3) {
                    if (dh == 0 and dw == 0) continue;
                    int nh = h+dh;
                    int nw = w+dw;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (grid[nh][nw] == '#') continue;
                    ll v = gridtoid(nh, nw, W);
                    nodes[u].eb(v, 1);
                }
            }
        }
    }
    ll s = gridtoid(sh, sw, W);
    ll t = gridtoid(th, tw, W);
    auto res = dijkstra(nodes, s, t);
    ll ans = res[t] < INF ? res[t] : -1;
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
