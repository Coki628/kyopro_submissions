/*
・きっちり自力AC。
・実験エスパー
・実験すると、奇数全部無理そうだね、となる。偶数は1個だけ使えばどうにでもなる。
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
    ll N;
    cin >> N;

    // rep(a, 30) {
    //     rep(b, 30) {
    //         rep(c, 30) {
    //             if ((a^b)+(b^c)+(c^a) == N) {
    //                 print(vector<ll>{a, b, c});
    //             }
    //         }
    //     }
    // }
    if (N%2 == 0) {
        print(vector<ll>{0, 0, N/2});
    } else {
        print(-1);
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
    while (T--) solve();

    return 0;
}
