/*
・きっちり自力AC。
・最短経路に帰着、ダイクストラ
・さっきやったやつの重み付きコスト版。
　やったばっかだからすぐ分かったけど、咄嗟にこれだけ出てきたら、
　グラフに帰着に気付くのに少し時間かかっちゃうかもしれない。
　こっちは問題の見た目が数列だから、気付けるかが勝負って感じ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "graph/_dijkstra.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvpil nodes(N);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
    }

    auto res = dijkstra(nodes, 0);
    ll ans = res[N-1];
    if (ans == INF) ans = -1;
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
