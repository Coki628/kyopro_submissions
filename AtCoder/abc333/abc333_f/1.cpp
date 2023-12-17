/*
・これは自力の延長上で書いた方針。これだと多分3乗DPから落ちない。。
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

    ModTools<mint> mt(N + 1);
    // dp[i] := i人いる状態で、ある人が先頭にいる確率
    // vector<mint> dp(N + 1);
    // dp[N] = 1;
    // rep(i, N, 1, -1) {
    //     mint total = pow(2LL, i, MOD);
    //     rep(j, i - 1, 0, -1) {
    //         // 遷移先 += 遷移元 * 自己ループ補正 * i-1人からj-1人残す(自分は絶対残すので-1) / 全通り
    //         dp[j] += dp[i] * (total / (total - 1)) * mt.nCr(i - 1, j - 1) / total;
    //     }
    // }
    // debug(dp[1]);

    vector<mint> ans(N);
    rep(k, N) {
        vector<mint> dp(N + 1);
        rep(i, k + 1) {
            // 初期状態から(kより前にいたやつらが)i人残って人kが先頭になる確率
            dp[N - (k - i)] = mt.nCr(k, i) / pow(2LL, k, MOD);
        }
        rep(i, N, 1, -1) {
            mint total = pow(2LL, i, MOD);
            rep(j, i - 1, 0, -1) {
                dp[j] += dp[i] * (total / (total - 1)) * mt.nCr(i - 1, j - 1) / total;
            }
        }
        ans[k] = dp[1];
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
