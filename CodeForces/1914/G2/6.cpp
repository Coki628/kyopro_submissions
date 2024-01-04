/*
参考：https://codeforces.com/contest/1914/submission/237988401
・別解、G1の続き。
・区間辺SCC
・区間辺の実装はこたつがめさんの提出を参考に作った。
・入次数を数えるのにはちょっと工夫が要る。
　区間辺の頂点から出発してるやつはカウントしちゃダメだけど、
　元頂点を出発して区間辺の頂点通ってる分は考慮しないとダメ。
　縮約グラフはDAGなので、前から順に上記に気をつけてちゃんと見て行けば大丈夫。
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

#include "graph/RangeEdgedSCC.hpp"

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
    RangeEdgedSCC scc(N);
    rep(i, N) {
        if (seg[A[i]].second == i) {
            ll j = seg[A[i]].first;
            scc.add_edge(i, j);
            scc.add_edge(j, i);
            scc.add_edges(i, j + 1, i);
            // rep(k, j + 1, i) {
            //     scc.add_edge(i, k);
            // }
        }
    }
    scc.build();
    scc.construct();
    ll N3 = scc.size();
    vvi nodes3(N3);
    for (auto [u, v] : scc.get_edges3()) {
        nodes3[u].eb(v);
    }
    // 入次数
    vector<ll> indeg(N3);
    ll mn = 0;
    mint cnt = 1;
    rep(u, N3) {
        if (scc.size(u) and indeg[u] == 0) {
            mn++;
            cnt *= scc.size(u);
        }
        if (scc.size(u) or indeg[u] > 0) {
            for (auto v : nodes3[u]) {
                indeg[v]++;
            }
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
