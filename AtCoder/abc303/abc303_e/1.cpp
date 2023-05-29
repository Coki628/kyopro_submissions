/*
・きっちり自力AC！
・次数3以上は確定。残りは3つ(次数2)ずつにする。
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
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<ll> ans;
    ll rest = N;
    rep(i, N) {
        ll sz = nodes[i].size();
        if (sz >= 3) {
            ans.eb(sz);
            rest -= sz + 1;
        }
    }
    assert(rest % 3 == 0);
    rep(_, rest / 3) {
        ans.eb(2);
    }
    sort(ALL(ans));
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
