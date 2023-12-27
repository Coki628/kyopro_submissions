/*
参考：https://atcoder.jp/contests/abc334/submissions/48778004
・これはTL見てしまっていたけっどライブラリ整備も兼ねて履修。
・グリッド、期待値、オフラインダイコネ
・TLでダイコネだとだいたいTLEみたいな話が流れてて、
　自分のうしさん版から改修してたやつ使ってみたけどやっぱりTLE。
　で、しょぼんさんがCFから速いダイコネ取ってきて通したって言ってたから、
　それを拝借して自分なりに使える形に整えた。
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

#include "graph/OfflineDynamicConnectivity.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    ll N = H * W;
    OfflineDynamicConnectivity odc(N);
    rep(h, H) {
        rep(w, W) {
            if (h + 1 < H and grid[h][w] == '#' and grid[h + 1][w] == '#') {
                ll u = gridtoid(h, w, W);
                ll v = gridtoid(h + 1, w, W);
                odc.add_edge(u, v);
            }
            if (w + 1 < W and grid[h][w] == '#' and grid[h][w + 1] == '#') {
                ll u = gridtoid(h, w, W);
                ll v = gridtoid(h, w + 1, W);
                odc.add_edge(u, v);
            }
        }
    }
    ll redcnt = 0;
    mint sm = 0, total = 0;
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '#') {
                ll u = gridtoid(h, w, W);
                total++;
                for (auto [dh, dw] : dir4) {
                    int nh = h + dh;
                    int nw = w + dw;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (grid[nh][nw] == '#') {
                        ll v = gridtoid(nh, nw, W);
                        odc.remove_edge(u, v);
                    }
                }
                odc.query();
                // 状態戻し
                for (auto [dh, dw] : dir4) {
                    int nh = h + dh;
                    int nw = w + dw;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (grid[nh][nw] == '#') {
                        ll v = gridtoid(nh, nw, W);
                        odc.add_edge(u, v);
                    }
                }
            } else {
                redcnt++;
            }
        }
    }
    odc.solve([&](ll i) {
        sm += odc.uf.size() - (redcnt + 1);
    });
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
