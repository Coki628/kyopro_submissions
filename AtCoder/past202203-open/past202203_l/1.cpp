/*
・終了後自力AC！
・定数項のある行列累乗
・同じ数字が増える変化をdpとして見ると、遷移が dp[i] = dp[i-1]*10+c
　で初期値0、遷移回数がdのように解釈できる。これは行列累乗に乗る。
　計算量、10万*2^3*log(10^12)なので重いけどC++のパワーで押し切る。AC0.65秒。
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
        vector<vector<mint>> mat = {
            {10, c},
            {0, 1},
        };
        vector<mint> init = {0, 1};
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
