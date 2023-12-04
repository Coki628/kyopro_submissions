/*
参考：https://codeforces.com/contest/1903/submission/235149307
・最小値の最大化、にぶたん、頂点被覆、区間辺2-SAT
・まず、頂点被覆とは、任意の各辺についてどちらかの端点はtrueだよ、みたいな話。
　確かにこれを実現するのに2-SATは相性が良さそう。
　で、もう1つの条件の、頂点番号の距離のminを最大化しなさいよというのは、
　これはもう明らかににぶたんを誘ってる。
　でもこれを素直にやろうとすると、距離の条件をつけるのにN^2必要で無理。
　そこで区間辺が必要になる。区間辺2-SATは自分は初見だったけど、
　強い人の間では結構ベタな典型みたいなので、頑張って取り込んでみた。
　おてらさんの実装がACLをうまくラップしてる感じですごく参考になった。
　使用側としてはなるべく頂点番号の変化とかを意識しないで済むように、
　呼び出し時には全て元頂点の番号で操作を呼べるようにした。結構うまく作れて満足。
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

#include "graph/RangeEdgedTwoSAT.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<pii> edges;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        edges.eb(u, v);
    }

    ll res = bisearch_max(1, N + 1, [&](ll x) {
        RangeEdgedTwoSAT ts(N);
        // 頂点被覆を満たすための条件
        for (auto [u, v] : edges) {
            // A or B
            ts.a_or_b(u, v);
        }
        // min(|Ai-Aj|)>=xを満たすための条件
        rep(u, N) {
            ts.add_clause(u, false, max(u - x + 1, 0LL), u, false);
            ts.add_clause(u, false, u + 1, min(u + x, N), false);
            // rep(v, u + 1, min(u + x, N)) {
            //     // not (A and B) 
            //     ts.not_a_and_b(u, v);
            // }
        }
        return ts.satisfiable();
    });
    print(res);
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
