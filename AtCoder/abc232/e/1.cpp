/*
・きっちり自力AC！
・状態を適切に減らすDP
・よく考察すると、必要な状態は4通りしかないことが分かる。
　後はK回遷移させればOK。場合分けが細かいので要注意力。詳細はソース内コメント。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    ll H, W, K;
    cin >> H >> W >> K;
    ll h1, w1, h2, w2;
    cin >> h1 >> w1 >> h2 >> w2;

    // 0: h2,w2以外, 1: h2でw2以外, 2: h2以外でw2, 3: h2かつw2
    auto dp = list2d<mint>(K+1, 4, 0);
    if (h1 == h2 and w1 == w2) {
        dp[0][3] = 1;
    } elif (h1 == h2) {
        dp[0][1] = 1;
    } elif (w1 == w2) {
        dp[0][2] = 1;
    } else {
        dp[0][0] = 1;
    }
    rep(i, K) {
        // 0 -> 1
        dp[i+1][1] += dp[i][0];
        // 0 -> 2
        dp[i+1][2] += dp[i][0];
        // 0 -> 0
        dp[i+1][0] += dp[i][0]*(H+W-4);

        // 1 -> 1
        dp[i+1][1] += dp[i][1]*(W-2);
        // 1 -> 3
        dp[i+1][3] += dp[i][1];
        // 1 -> 0
        dp[i+1][0] += dp[i][1]*(H-1);

        // 2 -> 2
        dp[i+1][2] += dp[i][2]*(H-2);
        // 2 -> 3
        dp[i+1][3] += dp[i][2];
        // 2 -> 0
        dp[i+1][0] += dp[i][2]*(W-1);

        // 3 -> 1
        dp[i+1][1] += dp[i][3]*(W-1);
        // 3 -> 2
        dp[i+1][2] += dp[i][3]*(H-1);
    }
    mint ans = dp[K][3];
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
