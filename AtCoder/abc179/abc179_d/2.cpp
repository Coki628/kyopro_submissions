/*
・dojo set_e_7_1
・きっちり自力AC！
・区間加算BIT
・貰うDPで累積和、BITで区間和、とかも考えたけど、思いつくうち最大の横着で通した。
　配るDPと区間加算BIT。理由はこれが一番早く書けて頭使わない、最短距離で解く方法だったから。
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

#include "segment/BIT2.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> L(K), R(K);
    rep(i, K) {
        cin >> L[i] >> R[i];
    }

    BIT2<mint> dp(N+1);
    dp.add(1, 1);
    rep(i, 1, N) {
        rep(j, K) {
            if (i+L[j] > N) continue;
            dp.add(i+L[j], min(i+R[j]+1, N+1), dp[i]);
        }
    }
    mint ans = dp[N];
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
