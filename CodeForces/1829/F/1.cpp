/*
・きっちり自力AC！
・次数を数えて、初代と2世代目で同数の時を場合分け。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<ll> C(N);
    rep(u, N) {
        C[nodes[u].size()]++;
    }
    ll one = -1, other = -1;
    rep(i, N) {
        if (C[i] == 1) {
            // 初代
            one = i;
        } else if (C[i] > 1) {
            // 2世代目
            other = i;
        }
    }
    assert(other != -1);
    if (one != -1) {
        ll x = one;
        ll y = other - 1;
        print(mkp(x, y));
    } else {
        ll x = other;
        ll y = other - 1;
        print(mkp(x, y));
    }
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
