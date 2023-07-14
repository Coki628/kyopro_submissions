/*
・自力AC！本番中はDで詰まりすぎてまともに考察できなかったものと思う。
・グラフに帰着、Functional Graph
・ゲーム内容を整理すると、有向グラフ上でサイクルに含まれる頂点であれば、
　後手は帳尻を合わせて勝つことができる。
　逆にサイクルに入る前だと、先手に十分大きい数を指定されると打つ手がなくなる。
　よってFunctional Graph上でサイクルに含まれる頂点を数える。
・やり方をどうやるかちょっと迷って、最初閉路検出みたいにDFS書いたんだけど、
　あんまり綺麗にまとまらなかったから再検討した。
　で、SCCで頂点数1の場合だけ分けて考えればいけそうだなってやったら無事AC。
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

#include "acl/scc.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;
    A--;

    vvi nodes(N);
    atcoder::scc_graph scc(N);
    rep(i, N) {
        nodes[i].eb(A[i]);
        scc.add_edge(i, A[i]);
    }
    auto groups = scc.scc();
    ll ans = 0;
    for (auto group : groups) {
        if (group.size() == 1) {
            ll u = group[0];
            if (nodes[u][0] == u) {
                ans++;
            }
        } else {
            ans += group.size();
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
