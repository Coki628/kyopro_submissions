/*
・dojo set_d_6_3
・なんとか自力AC！
・smallerもgreaterもある桁DP、leading zeroに気を付ける桁DP
・色々と大変な桁DP。JOIって感じだねぇ…。
　基本方針は割とすぐ出るけど、細部詰めが大変。
・添字はめちゃ多い。まず倍数の管理があって、smallerとgreaterの分、
　直前にジグザグのどっち向きに動いたか(ここにleading zero情報も含めた)、
　直前に選んだ数字、この5つに何番目まで見たかを合わせて6つ。
・遷移も、ジグザグしたかとleading zeroの兼ね合いでややこしい。
　なんかもう別関数みたいにした。
・leading zeroが続く間はジグザグしてなくても遷移できることに中々気付かなくて、
　解き切るのにすごく時間がかかってしまった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 10000;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
#include "template.hpp"

mint dp[507][507][2][2][3][10];

void solve() {
    string S, T;
    cin >> S >> T;
    ll M;
    cin >> M;

    ll N = T.size();
    S = zfill(S, N);
    dp[0][0][0][0][2][0] = 1;
    rep(n, N+1) {
        ll a = S[n] - '0';
        ll b = T[n] - '0';
        ll mul = pow(10, N-n-1, M);
        rep(m, M) {
            rep(i, 2) {
                rep(j, 2) {
                    rep(k, 3) {
                        rep(d, 10) {
                            if (dp[n][m][i][j][k][d] == 0) continue;
                            rep(nxd, 10) {
                                // greater確定前、aより小さいdはNG
                                if (i == 0 and a > nxd) continue;
                                // smaller確定前、bより大きいdはNG
                                if (j == 0 and b < nxd) continue;
                                ll nxi = a < nxd ? 1 : i;
                                ll nxj = b > nxd ? 1 : j;
                                ll nxk = [&]() -> ll {
                                    // ジグザグ開始前
                                    if (k == 2) {
                                        if (d == 0) {
                                            // leading zero
                                            return k;
                                        } else {
                                            // dが1桁目、nxdが2桁目
                                            if (d == nxd) return -1;
                                            if (d < nxd)  return 1;
                                            if (d > nxd) return 0;
                                        }
                                    } else {
                                        // ジグザグでないものはNG
                                        if (k == 0 and d >= nxd) return -1;
                                        if (k == 1 and d <= nxd) return -1;
                                        return 1 - k;
                                    }
                                }();
                                if (nxk == -1) continue;
                                dp[n+1][(m+nxd*mul)%M][nxi][nxj][nxk][nxd] += dp[n][m][i][j][k][d];
                            }
                        }
                    }
                }
            }
        }
    }
    mint ans = 0;
    rep(i, 2) {
        rep(j, 2) {
            rep(k, 3) {
                rep(d, 10) {
                    ans += dp[N][0][i][j][k][d];
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
