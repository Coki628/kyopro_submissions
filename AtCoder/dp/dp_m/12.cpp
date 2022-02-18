/*
・FPS演習
・二項だけ掛けるやつの動作確認。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
#include "template.hpp"

#include "math/FormalPowerSeries.hpp"
#include "math/fps/pow_term2.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    FPS<mint> fps(K+1);
    fps[0] = 1;
    rep(i, N) {
        // *= 1-x^(a+1)
        fps *= SFPS<mint>{{0, 1}, {A[i]+1, -1}};
    }
    // /= (1-x)^N
    fps *= pow_term2_inv(N, K+1);
    mint ans = fps[K];
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
