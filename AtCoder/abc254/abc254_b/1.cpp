/*
・BでDP？？？定義通りにDP書くと通る。
　でもこれは有名なパスカルのやつだし、遷移とかの定義も問題文に書いてあるので、
　BでDPが出たっていう内には入らないみたいだね…。
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

    auto dp = list2d(N, N, 0LL);
    rep(i, N) {
        rep(j, N) {
            if (j == 0 or j == i) {
                dp[i][j] = 1;
            } elif (i > 0) {
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            }
        }
    }
    rep(i, N) {
        auto res = subarray(dp[i], 0, i+1);
        print(res);
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
