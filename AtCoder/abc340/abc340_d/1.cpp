/*
・きっちり自力AC！
・グラフに帰着、ダイクストラ
・最初前からDPしそうになったけど、よく見たら後ろにも遷移する。
　ちょっと考えて、ダイクストラでいいね、となった。
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

#include "graph/dijkstra.hpp"

void solve() {
    ll N;
    cin >> N;
    vv<pil> nodes(N);
    rep(i, N - 1) {
        ll a, b;
        int x;
        cin >> a >> b >> x;
        x--;
        nodes[i].eb((int)i + 1, a);
        nodes[i].eb(x, b);
    }

    auto res = dijkstra(nodes, {0});
    print(res[N - 1]);
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
