/*
・FPS演習
・FPS、復元
・8回畳み込む。でもこれなら部分和DPでいいな…。
・FPS畳み込み用の繰り返し2乗法powを作ってみた。
　さすがにこれは8回しかないので速度変わらず。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define MINT_TO_LL_CAST
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

#include "math/FormalPowerSeries.hpp"

constexpr int m1 = 998244353;
constexpr int m2 = 1004535809;
constexpr int inv_m1_mod_m2 = 669690699;
using mint1 = ModInt<m1>;
using mint2 = ModInt<m2>;

long long garner(long long r1, long long r2) {
    long long t = (r2 - r1) * inv_m1_mod_m2;
    while (t < 0) t += m2;
    t %= m2;
    r1 += t * m1;
    return r1;
}

template<typename T>
void pow(FPS<T>& base, FPS<T> A, ll k, int deg=-1) {
    int n = deg;
    if (deg == -1) n = max(base.size(), A.size());
    while (k > 0) {
        if (k & 1) {
            base *= A;
            base.shrink(deg);
        }
        A *= A;
        A.shrink(deg);
        k >>= 1;
    }
}

void solve() {
    ll N;
    cin >> N;
    ll S = N*6;
    ll K = 8;

    // auto dp = list2d(K+1, S+1, 0LL);
    // dp[0][0] = 1;
    // rep(i, K) {
    //     rep(j, S+1) {
    //         rep(k, N+1) {
    //             if (j+k <= S) {
    //                 dp[i+1][j+k] += dp[i][j];
    //             }
    //         }
    //     }
    // }
    // auto ans = dp[K][S];
    // print(ans);

    FPS<mint1> A(N+1, 1), dpa(N+1);
    FPS<mint2> B(N+1, 1), dpb(N+1);
    dpa[0] = 1;
    dpb[0] = 1;
    pow(dpa, A, K, S+1);
    pow(dpb, B, K, S+1);
    // rep(_, K) {
    //     dpa *= A;
    //     dpb *= B;
    // }
    ll ans = garner(dpa[S], dpb[S]);
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
