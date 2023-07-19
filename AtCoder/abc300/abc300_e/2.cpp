/*
・ちょっと方針が自信なかったので復習。
　案の定うまくいかなくて、確率DPの自己ループありをどう処理したか思い出せず。
　なんか遷移無視するとかだった気がしたけど合わなくて、結局方針見たら、
　遷移無視っていうかそもそも分母からも消すんだったね。。
　でも真面目に都度式変形書く方がいい気がした。それが一番汎用的だよな。
・前回がmapのDPとメモ化再帰だったけど、
　今回は素因数の個数添字にして前からDPした。
　まあTLきつい訳じゃないんだし、mapでDPで良かったと思う。
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

    ll cnt2 = 0, cnt3 = 0, cnt5 = 0;
    ll cur = N;
    while (cur % 2 == 0) {
        cnt2++;
        cur /= 2;
    }
    while (cur % 3 == 0) {
        cnt3++;
        cur /= 3;
    }
    while (cur % 5 == 0) {
        cnt5++;
        cur /= 5;
    }
    if (cur > 1) {
        print(0);
        return;
    }

    auto dp = listnd(cnt2 + 1, cnt3 + 1, cnt5 + 1, (mint)0);
    dp[0][0][0] = 1;
    rep(i, cnt2 + 1) {
        rep(j, cnt3 + 1) {
            rep(k, cnt5 + 1) {
                dp[i][j][k];
                // 2
                if (i + 1 <= cnt2) {
                    dp[i + 1][j][k] += dp[i][j][k] / 5;
                }
                // 3
                if (j + 1 <= cnt3) {
                    dp[i][j + 1][k] += dp[i][j][k] / 5;
                }
                // 4
                if (i + 2 <= cnt2) {
                    dp[i + 2][j][k] += dp[i][j][k] / 5;
                }
                // 5
                if (k + 1 <= cnt5) {
                    dp[i][j][k + 1] += dp[i][j][k] / 5;
                }
                // 6
                if (i + 1 <= cnt2 and j + 1 <= cnt3) {
                    dp[i + 1][j + 1][k] += dp[i][j][k] / 5;
                }
            }
        }
    }
    mint ans = dp[cnt2][cnt3][cnt5];
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
