/*
・きっちり自力AC！
・行列累乗
・これは行列累乗一択で早かった。
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
#include "template.hpp"

#include "matrix/MatPow.hpp"

void solve() {
    ld x, y, z;
    ll K;
    cin >> x >> y >> z >> K;

    vector<vector<ld>> mat = {
        {1-x, y, 0},
        {0, 1-y, z},
        {x, 0, 1-z},
    };
    vector<ld> init = {1, 1, 1};
    MatPow<ld> mp;
    auto res = mp.solve(mat, init, K);
    print(res);
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
