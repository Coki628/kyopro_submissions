/*
・dojo set_d_6_6
・きっちり自力AC！
・bitDP、3^N集合DP
・これね、部分集合全部見るを合わせても計算量がO(3^N)で収まるやつ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto mat = list2d(N, N, 0LL);
    rep(i, N) {
        rep(j, N) {
            cin >> mat[i][j];
        }
    }

    vector<ll> dp(1LL<<N, 0);
    dp[0] = 0;
    rep(S, 1LL<<N) {
        // 集合Sのスコア
        rep(i, N) {
            rep(j, i+1, N) {
                if (S>>i & 1 and S>>j & 1) {
                    dp[S] += mat[i][j];
                }
            }
        }
        // 集合Sの部分集合の区切り方から、一番いいものを取る
        ll T = S;
        while (T > 0) {
            T = (T-1) & S;
            chmax(dp[S], dp[T] + dp[S^T]);
        }
    }
    ll ans = dp[(1LL<<N)-1];
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
