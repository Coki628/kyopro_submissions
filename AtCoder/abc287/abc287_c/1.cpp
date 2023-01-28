/*
・終了後自力AC…。
・直線グラフの判定
・6WAがとれずうんうん言ってスキップしたまま戻って来れず。
　結局、条件の1つで木判定するのに辺がN-1本であるチェックしかしてなくて、
　非連結サイクル付きみたいなやつを木だと判定してたのが原因…。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> C(N);
    UnionFind uf(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        C[u]++;
        C[v]++;
        uf.merge(u, v);
    }

    if (!(uf.size() == 1 and uf.is_tree(0))) {
        No();
        return;
    }
    auto C2 = Counter(C);
    if (C2[1] == 2 and C2[2] == N - 2) {
        Yes();
    } else {
        No();
    }
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
