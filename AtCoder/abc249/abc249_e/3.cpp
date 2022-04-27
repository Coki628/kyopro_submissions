/*
参考：https://atcoder.jp/contests/abc249/editorial/3844
・DP高速化、いもす法
・通常、貰うDPにして区間和取って高速化するタイプのDPを、
　いもす法を使って配るDPのままやる方法が紹介されていたのでやってみた。
・普段ほぼ配るDPでやるから、こっちのが直感的に分かりやすい気がした。
　今回よりもっと遷移が面倒な累積和DPで、実装が楽になるか今度試してみたい。
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

#include "segment/Imos.hpp"

void solve() {
    ll N, P;
    cin >> N >> P;
    mint::set_mod(P);

    vector<Imos<mint>> dp(N, {N+2});
    dp[0].add(0, 1);
    rep(i, N) {
        dp[i].build();
        rep(j, N) {
            if (dp[i][j] == 0) continue;
            rep(add, 2, 6) {
                if (i+add >= N) break;
                ll l = j + pow(10, add-2);
                ll r = j + pow(10, add-1);
                chmin(l, N+1);
                chmin(r, N+1);
                dp[i+add].add(l, r, dp[i][j] * (i == 0 ? 26 : 25));
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
