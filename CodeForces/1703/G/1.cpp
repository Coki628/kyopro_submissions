/*
・終了後、きっちり自力AC！
・割った回数を状態に持ってDP
・割る2の操作はlog回くらいやれば値が0になるので、それ以降は同一視でOK。
　これさえ状態に持てれば、後は適切に遷移とか作ればいい。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    ll L = 30;
    auto dp = listnd(N + 1, L + 1, -INF);
    dp[0][0] = 0;
    rep(i, N) {
        ll a = A[i];
        rep(j, L + 1) {
            chmax(dp[i + 1][j], dp[i][j] + a - K);
            a /= 2;
            chmax(dp[i + 1][min(j + 1, L)], dp[i][j] + a);
        }
    }
    ll ans = -INF;
    rep(j, L + 1) {
        chmax(ans, dp[N][j]);
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
