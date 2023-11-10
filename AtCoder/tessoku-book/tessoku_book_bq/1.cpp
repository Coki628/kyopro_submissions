/*
・フロー、最大流、二部マッチング
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

#include "acl/maxflow.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<string> grid(N);
    cin >> grid;

    atcoder::mf_graph<ll> mf(N * 2 + 2);
    ll s = N * 2, t = N * 2 + 1;
    rep(i, N) {
        mf.add_edge(s, i, 1);
        mf.add_edge(N + i, t, 1);
        rep(j, N) {
            if (grid[i][j] == '#') {
                mf.add_edge(i, N + j, 1);
            }
        }
    }
    ll ans = mf.flow(s, t);
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
