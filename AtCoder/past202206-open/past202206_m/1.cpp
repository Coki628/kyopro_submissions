/*
・自力TLEの期待値DP
　多分答えは合ってると思うんだけど、提出ほぼTLEなので分からない。
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
    ll N;
    cin >> N;

    auto memo = listnd(N + 1, N + 1, 2, (mint)0);
    auto visited = listnd(N + 1, N + 1, 2, 0);
    auto rec = [&](auto&& f, ll i, ll j, ll k) -> mint {
        if (i == N or j == N) {
            return 0;
        }
        if (visited[i][j][k]) {
            return memo[i][j][k];
        }
        visited[i][j][k] = true;
        mint res = 0;
        rep(x, 2) {
            ll ii = x == 0 ? i + 1 : i;
            ll jj = x == 1 ? j + 1 : j;
            ll kk = i == j and k != x ? 1 - k : k;
            ll p = k != kk ? 1 : 0;
            res += (f(f, ii, jj, kk) + p) / 2;
        }
        return memo[i][j][k] = res;
    };
    mint ans = (rec(rec, 1, 0, 0) + rec(rec, 0, 1, 1)) / 2;
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
