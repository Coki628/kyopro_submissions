/*
・自力AC。遅かったけど。。
・冪乗はすぐ大きくなるので、bとしてあり得る値は全探索できる。
・Div.3のAにしてはやたら重く感じたので、
　これ絶対割り算一発とかるんだろうなって思いながらやってたけど、
　やっぱりあったみたい。a=1固定で常にb=y/xだってよ…。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll x, y;
    cin >> x >> y;

    if (y%x != 0) {
        print(mkp(0, 0));
        return;
    }
    y /= x;
    if (y == 1) {
        print(mkp(1, 1));
        return;
    }

    rep(b, 2, y+1) {
        ll cur = 1;
        ll a = 0;
        while (cur < y) {
            cur *= b;
            a++;
        }
        if (cur == y) {
            print(mkp(a, b));
            return;
        }
    }
    print(mkp(0, 0));
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
