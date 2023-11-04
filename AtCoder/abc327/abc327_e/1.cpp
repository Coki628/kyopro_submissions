/*
・きっちり自力AC！
・後ろからDP
・reverseすれば遷移が最終的に選ぶ個数に依存しなくなるのでいける。
　計算式がちょっとややこしいけど、落ち着いて定数部分とか分ければOK。
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
    vector<ll> P(N);
    cin >> P;

    reverse(ALL(P));
    ld dp[N + 1][N + 1] = {};
    rep(i, N) {
        rep(j, N + 1) {
            chmax(dp[i + 1][j], dp[i][j]);
            if (j + 1 <= N) {
                chmax(dp[i + 1][j + 1], dp[i][j] + pow(0.9, j) * P[i]);
            }
        }
    }
    vector<ld> div(N + 1);
    rep(i, N) {
        div[i + 1] = div[i] + pow(0.9, i);
    }
    ld ans = -INF;
    rep(j, 1, N + 1) {
        chmax(ans, dp[N][j] / div[j] - 1200 / sqrt(j));
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
