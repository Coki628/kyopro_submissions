/*
・自力AC！
・Nも01列にエンコードして桁DP。
・と思ったけどTL見るとほぼみんな貪欲で解いてた…。
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
    ll N;
    cin >> N;

    string T = bin(N);
    ll M = max(S.size(), T.size());
    S = zfill(S, M);
    T = zfill(T, M);
    auto dp = listnd(M + 1, 2, -INF);
    dp[0][0] = 0;
    rep(i, M) {
        ll curval = 1LL << (M - i - 1);
        rep(j, 2) {
            if (dp[i][j] == -INF) continue;
            if (S[i] == '?') {
                rep(nxbit, 2) {
                    if (j == 0 and nxbit > (T[i] - '0')) continue;
                    ll nxj = nxbit < (T[i] - '0') or j;
                    chmax(dp[i + 1][nxj], dp[i][j] + curval * nxbit);
                }
            } else {
                ll nxbit = S[i] - '0';
                if (j == 0 and nxbit > (T[i] - '0')) continue;
                ll nxj = nxbit < (T[i] - '0') or j;
                chmax(dp[i + 1][nxj], dp[i][j] + curval * nxbit);
            }
        }
    }
    ll res = max(dp[M][0], dp[M][1]);
    ll ans = res == -INF ? -1 : res;
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
