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
    ll N, M, L = 24;
    cin >> N >> M;
    vector<string> mat(N);
    cin >> mat;

    atcoder::mf_graph<ll> mf(N + L + 2);
    ll s = N + L;
    ll t = N + L + 1;
    rep(i, N) {
        mf.add_edge(s, i, 10);
        rep(j, L) {
            if (mat[i][j] == '1') {
                mf.add_edge(i, N + j, 1);
            }
        }
    }
    rep(i, L) {
        mf.add_edge(N + i, t, M);
    }
    ll res = mf.flow(s, t);
    print(res == M * L ? "Yes" : "No");
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
