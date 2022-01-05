/*
・きっちり自力AC！
・ほぼLCSのDP。条件1個だけ逆にする。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    string a, b;
    cin >> a >> b;
    int N = a.size();
    int M = b.size();

    auto dp = list2d(N+1, M+1, 0LL);
    rep(i, N+1) {
            rep(j, M+1) {
            if (i < N) {
                chmax(dp[i+1][j], dp[i][j]);
            }
            if (j < M) {
                chmax(dp[i][j+1], dp[i][j]);
            }
            if (i < N && j < M && a[i] != b[j]) {
                chmax(dp[i+1][j+1], dp[i][j]+1);
            }
        }
    }
    ll ans = dp[N][M];
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
