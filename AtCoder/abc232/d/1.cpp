/*
・きっちり自力AC！
・グリッドDP
・絶対Cより簡単に思える。やり方知ってれば。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    rep(i, H) cin >> grid[i];

    auto dp = list2d(H, W, -INF);
    dp[0][0] = 1;
    ll ans = 1;
    rep(i, H) {
        rep(j, W) {
            if (i+1 < H and grid[i+1][j] == '.') {
                chmax(dp[i+1][j], dp[i][j]+1);
            }
            if (j+1 < W and grid[i][j+1] == '.') {
                chmax(dp[i][j+1], dp[i][j]+1);
            }
            chmax(ans, dp[i][j]);
        }
    }
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
