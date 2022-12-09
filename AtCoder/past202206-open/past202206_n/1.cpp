/*
・間に合わず終了後AC。Eの添字で消耗したのが良くなかった…。
・最小カット復元
・ABCで出た時覚えたのでACLにあるのは知ってた。
　辺ではなく頂点コストなのでin,outで頂点2倍にしてそこにコストの辺張る。
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

#include "acl/maxflow.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    auto grid = listnd(H, W, 0LL);
    cin >> grid;

    ll N = H * W;
    ll s = gridtoid(0, 0, W);
    ll t = gridtoid(H - 1, W - 1, W) + N;
    atcoder::mf_graph<ll> mf(N * 2);
    rep(h, H) {
        rep(w, W) {
            ll in = gridtoid(h, w, W);
            ll out = gridtoid(h, w, W) + N;
            mf.add_edge(in, out, grid[h][w] > 0 ? grid[h][w] : INF);
            ll u = gridtoid(h, w, W) + N;
            for (auto [dh, dw] : dir4) {
                ll nh = h + dh;
                ll nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W)
                    continue;
                ll v = gridtoid(nh, nw, W);
                mf.add_edge(u, v, INF);
            }
        }
    }
    auto mx = mf.flow(s, t);
    print(mx);
    auto cut = mf.min_cut(s);
    vector<string> ans(H, string(W, '.'));
    rep(h, H) {
        rep(w, W) {
            ll in = gridtoid(h, w, W);
            ll out = gridtoid(h, w, W) + N;
            if (cut[in] != cut[out]) {
                ans[h][w] = '#';
            }
        }
    }
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
