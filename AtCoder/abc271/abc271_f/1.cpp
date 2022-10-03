/*
・これは本番中の自力TLE。
　ワンチャン状態数少なければみたいな愚かなやつ。
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
    auto grid = listnd(N, N, 0LL);
    rep(i, N) {
        rep(j, N) {
            cin >> grid[i][j];
        }
    }

    auto dp = listnd(N, N, HashMap<ll, ll>());
    dp[0][0][grid[0][0]] = 1;
    rep(i, N) {
        rep(j, N) {
            for (auto [k, v] : dp[i][j]) {
                if (i+1 < N) {
                    dp[i+1][j][grid[i+1][j]^k] += v;
                }
                if (j+1 < N) {
                    dp[i][j+1][grid[i][j+1]^k] += v;
                }
            }
        }
    }
    ll ans = dp[N-1][N-1][0];
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
