/*
・2変数の桁DP
・絶対想定解じゃなさそうな地獄みたいな解法が思いついてしまったけど、
　練習のため実装してみた。2変数の桁DPめったにやらないしね。
・先頭の桁が何だったか覚えておけば、末尾桁の遷移時に妥当かチェックすればいける。
　N以下の条件のためのsmaller flagと、leading zeroが終わったかどうかを、
　A,Bそれぞれについて持って、先頭の桁もそれぞれ覚えて、
　(index以外で)計6個の添字で状態を持つと、桁DPが成立して通る。
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
    string S;
    cin >> S;
    ll N = S.size();

    ll dp[N + 1][10][10][2][2][2][2] = {};
    dp[0][0][0][0][0][0][0] = 1;
    rep(i, N) {
        ll a = S[i] - '0';
        rep(d1, 10) {
            rep(d2, 10) {
                rep(f1, 2) {
                    rep(f2, 2) {
                        rep(j, 2) {
                            rep(k, 2) {
                                if (dp[i][d1][d2][f1][f2][j][k] == 0) continue;
                                rep(nd1, 10) {
                                    if (f1 == 0 and nd1 > a) continue;
                                    rep(nd2, 10) {
                                        if (f2 == 0 and nd2 > a) continue;
                                        // smaller flag
                                        ll nf1 = f1 | (nd1 < a);
                                        ll nf2 = f2 | (nd2 < a);
                                        // leading zero
                                        ll nj = j | (nd1 > 0);
                                        ll nk = k | (nd2 > 0);
                                        // 先頭桁
                                        ll nnd1 = (j == 0 and nj == 1) ? nd1 : d1;
                                        ll nnd2 = (k == 0 and nk == 1) ? nd2 : d2;
                                        // 末尾桁の条件チェック
                                        if (i == N - 1 and (nnd1 != nd2 or nd1 != nnd2)) continue;
                                        dp[i + 1][nnd1][nnd2][nf1][nf2][nj][nk] += dp[i][d1][d2][f1][f2][j][k];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    ll ans = 0;
    rep(d1, 10) {
        rep(d2, 10) {
            rep(f1, 2) {
                rep(f2, 2) {
                    ans += dp[N][d1][d2][f1][f2][1][1];
                }
            }
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
