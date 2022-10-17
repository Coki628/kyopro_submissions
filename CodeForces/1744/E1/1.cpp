/*
・自力AC！と思ったらハックされた…。
・約数列挙
・目当てのペアはa*bの倍数である必要があるので、abで篩みたいなループして、
　これをxy→x*yと分解したいので約数列挙。
　範囲内のx,yが見つかれば出力、c*dまで探して無ければ-1とした。
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
    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    ll ab = a * b;
    ll cd = c * d;
    rep(i, ab, cd+1, ab) {
        for (auto x : divisors(i)) {
            ll y = i / x;
            if (a < x and x <= c and b < y and y <= d) {
                print(mkp(x, y));
                return;
            }
        }
    }
    print(mkp(-1, -1));
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
