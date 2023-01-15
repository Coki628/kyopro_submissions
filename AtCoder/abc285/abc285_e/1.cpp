/*
・なんとか自力AC！
・区切るDP
・前の休日からの距離で利得は一定なので前計算しておく。
　直前に休んだ日を状態に持ってDP。区切り位置全部見る遷移をやる。
　円環の扱いにしばらく悩んだけど、利得が位置でなく距離にしか依存しないので、
　実は普通にやるだけでいい。(もうちょい早く気付きたかった…。)
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    vector<ll> B(N);
    rep(len, 1, N) {
        rep(j, len) {
            B[len] += A[min(j, len - j - 1)];
        }
    }
    vector<ll> dp(N + 1, -INF);
    dp[0] = 0;
    rep(i, 1, N + 1) {
        rep(j, i) {
            chmax(dp[i], dp[j] + B[i - j - 1]);
        }
    }
    ll ans = dp[N];
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
