/*
・きっちり自力AC！これ結構早かった。
・ようは区間を01で見て、xorして1~N全部が1になるような区間の集合があればいいと思うんだけど悩んだ。
　区間の始点と終点を辺でつないだグラフでBFSとかしてNまで到達できるか、みたいにやった。
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

#include "graph/bfs.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vvi nodes(N+1);
    rep(i, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        nodes[l].eb(r);
        nodes[r].eb(l);
    }

    auto res = bfs(nodes, {0});
    if (res[N] < INF) Yes();
    else No();
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
