/*
ライブラリ整備：オイラーツアー
・一応verifyしておく。
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

#include "graph/EulerTour.hpp"
#include "datastructure/WaveletMatrix.hpp"
#include "datastructure/BIT2.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    
    EulerTour et(nodes);
    WaveletMatrix<ll> wm(N);
    BIT2<ll> bit(N);
    rep(u, N) {
        wm.set(et[u], u);
    }
    wm.build();

    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            // 頂点uと部分木側にあるx<uとなる(x,u)ペアを、根側への寄与とする
            ll vcnt = wm.range_freq(et.in[v], et.out[v], 0, u);
            bit.add(0, et.in[v], vcnt);
            bit.add(et.out[v], N, vcnt);
            // 頂点vと根側にあるx<vとなる(x,v)ペアを、部分木側への寄与とする
            vcnt = wm.range_freq(0, et.in[v], 0, v) + wm.range_freq(et.out[v], N, 0, v);
            bit.add(et.in[v], et.out[v], vcnt);
        }
    };
    dfs(dfs, 0, -1);

    vector<ll> ans(N);
    rep(u, N) {
        ans[u] = bit[et[u]];
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
