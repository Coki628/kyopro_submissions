/*
・これは本番中に途中まで書いてた愚直を完成させたもの。TLE想定。
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
// using mint = ModInt<MOD>;
#include "template.hpp"

#include "combinatorics/ArbitraryModInt.hpp"
using mint = ArbitraryModInt;

mint dp[3007][3007];

void solve() {
    ll N, P;
    cin >> N >> P;
    mint::set_mod(P);

    dp[0][0] = 1;
    rep(i, N-1) {
        rep(j, N) {
            if (dp[i][j] == 0) continue;
            rep(k, 1, N+1) {
                ll add = k < 10 ? 2 : k < 100 ? 3 : k < 1000 ? 4 : 5;
                if (i+add >= N or j+k > N) break;
                dp[i+add][j+k] += dp[i][j] * (i == 0 ? 26 : 25);
            }
        }
    }
    mint ans = 0;
    rep(i, 1, N) {
        ans += dp[i][N];
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
