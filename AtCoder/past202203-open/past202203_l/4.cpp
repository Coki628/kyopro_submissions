/*
・行列累乗ライブラリ改修
・行列をvectorではなくarrayで作った版。
　思った通り速くなって、0.65秒→0.21秒に。
　行列サイズが定数の行列累乗は常にこっち使った方がいいかな。
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
// using mint = ModInt<MOD>;
#include "template.hpp"

#include "matrix/MatPow.hpp"
#include "combinatorics/ArbitraryModInt.hpp"
using mint = ArbitraryModInt;

void solve() {
    ll K, M;
    cin >> K >> M;
    mint::set_mod(M);

    MatPow<mint> mp;
    mint ans = 0;
    rep(i, K) {
        ll c, d;
        cin >> c >> d;
        ans *= pow(10, d, M);
        array<array<mint, 2>, 2> mat = {{
            {10, c},
            {0, 1},
        }};
        array<mint, 2> init = {0, 1};
        auto res = mp.solve(mat, init, d);
        ans += res[0];
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
