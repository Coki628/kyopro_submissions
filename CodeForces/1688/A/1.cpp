/*
・きっちり自力AC！
・まずはAND条件がいけるか下から見て、いけるビット立てて、そのビット以外も立ってたらそこでOK。
　そのビットしか立ってなかったら、また下から見て、今度は立ってないビット見つけたらXOR条件を満たすために立てる。
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
    ll x;
    cin >> x;

    ll y = 0;
    rep(k, 31) {
        if (x>>k & 1) {
            y |= 1LL<<k;
            if (y == x) {
                break;
            } else {
                print(y);
                return;
            }
        }
    }
    rep(k, 31) {
        if (!(x>>k & 1)) {
            y |= 1LL<<k;
            break;
        }
    }
    print(y);
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
