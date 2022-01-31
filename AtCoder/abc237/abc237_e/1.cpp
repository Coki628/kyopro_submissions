/*
参考：https://snuke.hatenablog.com/entry/2021/02/22/102734
　　　https://theory-and-me.hatenablog.com/entry/2019/09/08/182442
・自力AC！かと思えば嘘で、after_contestのケースに撃墜された。。
・ダイクストラ
・負辺あったらダイクストラ駄目だろと思ったら負閉路ないから大丈夫だった、
　と思ったらダメだった。TLに流れてた上記参考文献を参照。
　今回は制約的にそういうケース作れないんかなー、とも思ったんだけど、
　ちゃんと作れるようで、しっかりafter_contestに落とされた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

#include "graph/_dijkstra.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    auto H = LIST(N);

    vvpll nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        if (H[u] <= H[v]) {
            nodes[u].eb(v, (H[v]-H[u])*2);
            nodes[v].eb(u, -(H[v]-H[u]));
        } else {
            nodes[u].eb(v, -(H[u]-H[v]));
            nodes[v].eb(u, (H[u]-H[v])*2);
        }
    }

    auto res = dijkstra(nodes, 0);
    ll ans = -min(res);
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
