/*
・自力AC！
・グリッド、斜め線
・一度で2本消せるマスを数える。いくつか図に書くと規則が見えて、N+N-2だと分かる。
　これで全部いけるなら切り上げ割る2だし、
　足りなければ残り1を本ずつ消していくとすればOK。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

void solve(int testcase) {
    ll N, K;
    cin >> N >> K;

    ll cnt2 = N + N - 2;
    if (K <= cnt2 * 2) {
        ll res = ceil(K, 2LL);
        print(res);
    } else {
        K -= cnt2 * 2;
        ll res = cnt2 + K;
        print(res);
    }
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
    rep(t, T) solve(t);

    return 0;
}
