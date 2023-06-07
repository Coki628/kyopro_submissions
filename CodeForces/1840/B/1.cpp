/*
・自力AC。
・実験エスパー。min(pow(2,K),N+1)を溢れないようにやる。何でこれかは知らん。
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

void solve() {
    ll N, K;
    cin >> N >> K;

    // rep(n, 1, 10) {
    //     rep(k, 1, 10) {
    //         ll ans = 0;
    //         rep(bit, 1LL << k) {
    //             ll cost = 0;
    //             rep(i, k) {
    //                 if (bit >> i & 1) {
    //                     cost += 1LL << i;
    //                 }
    //             }
    //             if (cost <= n) {
    //                 ans++;
    //             }
    //         }
    //         print(mkp(n, k));
    //         print(ans);
    //         print();
    //     }
    // }

    ll ans = 1;
    rep(_, K) {
        if (ans * 2 >= N + 1) {
            ans = N + 1;
            break;
        }
        ans *= 2;
    }
    print(ans);
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
