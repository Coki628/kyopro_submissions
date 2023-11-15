/*
・きっちり自力AC！
・行列累乗
・行列累乗久々に書いた割には遷移行列とか手際よく書けたと思う。
・公式解説見た。2列目以降の遷移全部7通りらしい。。行列書いた時間返してくれ。
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

#include "matrix/MatPow.hpp"

void solve() {
    ll W;
    cin >> W;

    ll N = 4;
    ll NN = N * N;
    array<array<mint, 16>, 16> mat = {};
    rep(c1, N) {
        rep(c2, N) {
            if (c1 == c2) continue;
            rep(c3, N) {
                if (c1 == c3) continue;
                rep(c4, N) {
                    if (c2 == c4) continue;
                    ll i = c1 * N + c2;
                    ll j = c3 * N + c4;
                    mat[i][j] = 1;
                }
            }
        }
    }
    array<mint, 16> init = {};
    rep(c1, N) {
        rep(c2, N) {
            if (c1 == c2) continue;
            ll i = c1 * N + c2;
            init[i] = 1;
        }
    }
    MatPow<mint> mp;
    auto res = mp.solve(mat, init, W - 1);
    mint ans = 0;
    rep(i, NN) ans += res[i];
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
