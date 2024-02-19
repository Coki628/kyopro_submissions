/*
・自力AC！
・K番目の値、倍数の個数、ベン図、包除、にぶたん
・両方の倍数は重複として引く。両方引くので*2するのを最初見落とし。
　lcmじゃなくてN*Mでやってしまっていて1ペナ…。
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

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;

    ll NM = lcm(N, M);
    ll res = bisearch_min(0, INF, [&](ll x) {
        ll cntn = x / N;
        ll cntm = x / M;
        ll cntnm = x / NM;
        return cntn + cntm - cntnm * 2 >= K;
    });
    print(res);
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
