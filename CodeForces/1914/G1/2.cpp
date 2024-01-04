/*
参考：https://twitter.com/keroru10/status/1737157781596352765
　　　https://codeforces.com/contest/1914/submission/238034311
・別解も学びが多そうなのでやる。
・SCC、グラフの縮約
・keroruさんのを参考にした。こっちの方針の人のが多いのかも。
　交差する区間に双方向、内包する区間に外→内の片方向、
　同色の左端と右端に双方向で、それぞれ有向辺を張る。
　このグラフをSCCして縮約すると、(自己ループ以外で)入次数0の成分が、
　交差する複数の区間のひとまとまりに対応する。
　あとはUFでやったのと同様に数えればOK。
・なお、この後G2を解くのに区間辺を張りたいので、
　頂点を色ではなく区間上の位置の方に対応させた。
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

#include "graph/SCC.hpp"

void solve() {
    ll N;
    cin >> N;
    N *= 2;
    vector<ll> A(N);
    cin >> A;
    A--;

    vector<pll> seg(N, {-1, -1});
    rep(i, N) {
        if (seg[A[i]].first == -1) {
            seg[A[i]].first = i;
        } else {
            seg[A[i]].second = i;
        }
    }
    SCC scc(N);
    rep(i, N) {
        if (seg[A[i]].second == i) {
            ll j = seg[A[i]].first;
            scc.add_edge(i, j);
            scc.add_edge(j, i);
            rep(k, j + 1, i) {
                scc.add_edge(i, k);
            }
        }
    }
    scc.build();
    scc.construct();
    ll N2 = scc.size();
    // 入次数
    vector<ll> indeg(N2);
    for (auto [u, v] : scc.get_edges2()) {
        if (u == v) continue;
        indeg[v]++;
    }
    ll mn = 0;
    mint cnt = 1;
    rep(u, N2) {
        if (indeg[u] == 0) {
            mn++;
            cnt *= scc.size(u);
        }
    }
    print(mkp(mn, cnt));
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
