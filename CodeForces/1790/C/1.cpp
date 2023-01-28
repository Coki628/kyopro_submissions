/*
・きっちり自力AC！
・結局、各数列の先頭要素だけ見れば全部分かる。
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
    vvl P(N);
    rep(i, N) {
        rep(j, N - 1) {
            ll p;
            cin >> p;
            P[i].eb(p);
        }
    }

    vvl adj(N + 1);
    rep(i, N) {
        adj[P[i][0]].eb(i);
    }
    ll x = -1, y = -1;
    rep(i, 1, N + 1) {
        if (adj[i].size() == 1) {
            x = adj[i][0];
        } else if (adj[i].size() > 1) {
            y = adj[i][0];
        }
    }
    assert(x != -1 and y != -1);
    vector<ll> ans = P[x];
    ans.insert(ans.begin(), P[y][0]);
    print(ans);
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
