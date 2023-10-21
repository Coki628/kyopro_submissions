/*
・きっちり自力AC！
・前後からダイクストラで中継地全探索
・なんだけど、制約2乗OKなので、もっと愚直なやつでも大丈夫だと思う。
　でもそれだとEって易しすぎない？なんでこの制約にしたんだろ。
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
    ll N, x, y, z;
    cin >> N >> x >> y >> z;
    auto D = listnd(N, N, 0LL);
    rep(i, N) {
        rep(j, N) {
            cin >> D[i][j];
        }
    }

    vvpil nodes1(N), nodes2(N);
    rep(i, N) {
        rep(j, N) {
            nodes1[i].eb(j, D[i][j] * x);
            nodes2[i].eb(j, D[i][j] * y + z);
        }
    }
    auto res1 = dijkstra(nodes1, 0);
    auto res2 = dijkstra(nodes2, N - 1);
    ll ans = INF;
    rep(i, N) {
        chmin(ans, res1[i] + res2[i]);
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
