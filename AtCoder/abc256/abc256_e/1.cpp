/*
・自力AC！
・順列、有向グラフ、SCC
・サイクルになってたらどれか1つは犠牲に。有向グラフのサイクル検出なのでSCCする。
　確証はなかったけど信じて投げる。
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
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    auto X = LIST(N);
    rep(i, N) X[i]--;
    auto C = LIST(N);

    scc_graph scc(N);
    rep(i, N) {
        scc.add_edge(i, X[i]);
    }
    auto groups = scc.scc();
    ll ans = 0;
    for (auto& group : groups) {
        if (group.size() > 1) {
            ll mn = INF;
            for (ll u : group) {
                chmin(mn, C[u]);
            }
            ans += mn;
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
