/*
・きっちり自力AC！
・1個前を切り替えたか、今連続させてる回数の偶奇、の2*2を状態に持ってDP。
　これが結構すんなり思いついたからB2もそのままの流れで解けてよかった。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;

    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] - '0';
    }
    // j = 1個前を切り替えたか, k = 今連続させてる回数の偶奇, {操作回数}
    auto dp = list3d(N+1, 2, 2, INF);
    dp[1][0][1] = 0;
    dp[1][1][1] = 1;
    rep(i, 1, N) {
        rep(j, 2) {
            ll prv = A[i-1] ^ j;
            rep(k, 2) {
                rep(jj, 2) {
                    ll cur = A[i] ^ jj;
                    if (k%2 == 1 and prv != cur) continue;
                    ll kk = prv == cur ? 1-k : 1;
                    ll add = jj;
                    chmin(dp[i+1][jj][kk], dp[i][j][k] + add);
                }
            }
        }
    }
    ll ans = INF;
    rep(j, 2) {
        chmin(ans, dp[N][j][0]);
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
