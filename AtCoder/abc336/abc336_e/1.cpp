/*
・自力AC！
・桁DP
・出てくる桁和はせいぜい130くらいまで。
　最後の桁和がいくつになるか決まると桁DPできるので、
　それを全探索してxとして、
　dp[i][j][k][l] := i桁目まで決めて、桁和がj、値 mod xがk、smallerフラグがl
　って4次元DPした。答えにはj==xな場合(つまり桁和が本当にxになった場合)のみ使う。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    string S;
    cin >> S;
    ll N = S.size();

    // 9 * 14 = 126
    ll M = 130;
    ll ans = 0;
    rep(mod, 1, M) {
        // auto dp = listnd(N + 1, M, mod, 2, 0LL);
        ll dp[N + 1][M][mod][2] = {};
        dp[0][0][0][0] = 1;
        rep(i, N) {
            ll val = toint(S[i]);
            rep(j, M) {
                rep(k, mod) {
                    rep(l, 2) {
                        if (dp[i][j][k][l] == 0) continue;
                        rep(d, 10) {
                            if (l == 0 and d > val) continue;
                            ll nxl = l or (d < val);
                            ll nxj = j + d;
                            ll nxk = (k * 10 + d) % mod;
                            dp[i + 1][nxj][nxk][nxl] += dp[i][j][k][l];
                        }
                    }
                }
            }
        }
        rep(j, M) {
            if (j == mod) {
                ans += dp[N][j][0][0] + dp[N][j][0][1];
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
