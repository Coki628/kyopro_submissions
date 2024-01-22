/*
参考：https://atcoder.jp/contests/abc337/editorial
　　　https://www.youtube.com/watch?v=-FSFsz9u_N0
・自力ならず。。グラフはこのレベルまで解いていきたいよね…。
・木グラフ、転倒数、列挙
・寄与、オイラーツアー、部分木クエリ、range_freq、区間加算
・全方位っぽい問われ方だけど、全方位に乗せる必要はない。(全方位でも解けるらしいが…)
　各辺に注目しつつ、題意のu-w-vの真ん中になるwに注目すると、
　その時の部分木側が根側に与える寄与と、根側が部分木側に与える寄与が求まれば、
　これを全部の辺で網羅した時、全ての頂点を根とした時の寄与も与え終わる。
　木での列挙に対するこのアプローチは多分初めてやったので、モノにして手札としておきたい。
　ここのやり方さえ分かれば、後必要なのは部分木クエリにオイラーツアー、
　range_freqにWM、区間加算のBITと、ライブラリを活躍させて簡潔にやれる。
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

#include "graph/HeavyLightDecomposition.hpp"
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
    
    HeavyLightDecomposition hld(nodes);
    WaveletMatrix<ll> wm(N);
    BIT2<ll> bit(N);
    rep(u, N) {
        wm.set(hld[u], u);
    }
    wm.build();

    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            // 頂点uと部分木側にあるx<uとなる(x,u)ペアを、根側への寄与とする
            ll vcnt = wm.range_freq(hld.in[v], hld.out[v], 0, u);
            bit.add(0, hld.in[v], vcnt);
            bit.add(hld.out[v], N, vcnt);
            // 頂点vと根側にあるx<vとなる(x,v)ペアを、部分木側への寄与とする
            vcnt = wm.range_freq(0, hld.in[v], 0, v) + wm.range_freq(hld.out[v], N, 0, v);
            bit.add(hld.in[v], hld.out[v], vcnt);
        }
    };
    dfs(dfs, 0, -1);

    vector<ll> ans(N);
    rep(u, N) {
        ans[u] = bit[hld[u]];
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
