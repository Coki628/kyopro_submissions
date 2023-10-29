/*
・貪欲
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

#include "geometry/Point.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<Point<ld>> P(N);
    rep(i, N) {
        cin >> P[i].x >> P[i].y;
    }

    vector<ll> ans = {0}, visited(N);
    ll cur = 0;
    ld sm = 0;
    visited[0] = 1;
    rep(_, N - 1) {
        ll nxt = -1;
        ld mn = INF;
        rep(i, N) {
            if (visited[i]) continue;
            if (chmin(mn, P[cur].abs(P[i]))) {
                nxt = i;
            }
        }
        visited[nxt] = 1;
        ans.eb(nxt);
        cur = nxt;
        sm += mn;
    }
    ans.eb(0);
    sm += P[cur].abs(P[0]);
    ld score = 1e6 / sm;

    debug(sm);
    debug(score);
    ans++;
    print(ans, '\n');
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
