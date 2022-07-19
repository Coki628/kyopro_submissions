/*
・きっちり自力AC！
・N奇数は一択。偶数ならDPする。取った/取らないの差分が+-2くらいだけ持つDP。
　(ABC162fがこれと同じ感じのDP。ちゃんとやり方思い出せて良かった。)
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
    auto A = LIST(N);

    if (N%2 == 1) {
        ll ans = 0;
        rep(i, 1, N-1, 2) {
            ll cost = max(max(A[i-1], A[i+1]) - A[i] + 1, 0LL);
            ans += cost;
        }
        print(ans);
        return;
    }

    auto dp = list2d(N, 2, defaultdict<ll, ll>{INF});
    dp[1][0][0] = 0;
    rep(i, 1, N-1) {
        rep(j, -2, 3) {
            chmin(dp[i+1][0][j-1], dp[i][0][j]);
            chmin(dp[i+1][0][j-1], dp[i][1][j]);
            ll cost = max(max(A[i-1], A[i+1]) - A[i] + 1, 0LL);
            chmin(dp[i+1][1][j+1], dp[i][0][j] + cost);
        }
    }
    ll ans = min(dp[N-1][0][0], dp[N-1][1][0]);
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
