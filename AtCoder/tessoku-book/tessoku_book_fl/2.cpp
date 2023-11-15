/*
・公式解の方針が結構違った。
・一般グラフ・無向重み付き、最短経路
・ダイクストラ、中継地全探索
・中継地全探索で1とNからそれぞれの最短経路が、
　1~Nの最短経路と一致していれば使えるということになる。
　言われたら確かにそう。。
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

#include "graph/_dijkstra.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvpil nodes(N);
    rep(i, M) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        nodes[a].eb(b, c);
        nodes[b].eb(a, c);
    }

    auto dist1 = dijkstra(nodes, {0});
    auto dist2 = dijkstra(nodes, {(int)N - 1});
    ll ans = 0;
    rep(i, N) {
        if (dist1[i] + dist2[i] == dist1[N - 1]) {
            ans++;
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
