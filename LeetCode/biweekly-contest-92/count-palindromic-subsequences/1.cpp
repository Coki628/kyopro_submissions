/*
・きっちり自力AC！
・回文、DP
・5文字の回文なので大事なのは1,2文字目。これらと合うような4,5文字目だけ遷移させる。
　dp[i][j][k1][k2] := i番目まで見てj文字決めて、1文字目がk1で2文字目がk2 みたいにする。
・なんか答え合わないなーって言ってたら、暗黙マルチテストケースみたいなやつだった。
　メソッド内でちゃんと初期化処理入れたら無事AC。
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

mint dp[10007][6][10][10];

class Solution {
public:
    int countPalindromes(string S) {
        ll N = S.size();
        ll M = 5;
        rep(i, N+1) rep(j, M+1) rep(k1, 10) rep(k2, 10) dp[i][j][k1][k2] = 0;
        dp[0][0][0][0] = 1;
        rep(i, N) {
            rep(j, M+1) {
                rep(k1, 10) {
                    rep(k2, 10) {
                        dp[i+1][j][k1][k2] += dp[i][j][k1][k2];
                        if (j+1 <= M) {
                            if (j == 0) {
                                dp[i+1][j+1][S[i]-'0'][k2] += dp[i][j][k1][k2];
                            } elif (j == 1) {
                                dp[i+1][j+1][k1][S[i]-'0'] += dp[i][j][k1][k2];
                            } elif (j == 2) {
                                dp[i+1][j+1][k1][k2] += dp[i][j][k1][k2];
                            } elif (j == 3) {
                                if (S[i]-'0' == k2) {
                                    dp[i+1][j+1][k1][k2] += dp[i][j][k1][k2];
                                }
                            } elif (j == 4) {
                                if (S[i]-'0' == k1) {
                                    dp[i+1][j+1][k1][k2] += dp[i][j][k1][k2];
                                }
                            }
                        }
                    }
                }
            }
        }
        mint ans = 0;
        rep(k1, 10) {
            rep(k2, 10) {
                ans += dp[N][M][k1][k2];
            }
        }
        return ans.x;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        auto res = sol.countPalindromes("9999900000");
        // print(res);
        return 0;
    }
#endif
