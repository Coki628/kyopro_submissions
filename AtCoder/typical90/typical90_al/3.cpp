/*
・E8さん本より
・きっちり自力AC！
・前やった時はPythonに逃げたので、今回はちゃんとC++で通した。
　オーバーフロー対策済。
　なんだけど1WAで、10^18を小数型の1e18使ってたのllに直したら通った。
　やっぱ小数だとダメだねー、誤差。
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

void solve() {
    ll a, b;
    cin >> a >> b;

    // ll lcm(ll x, ll y) { return x/gcd(x, y)*y; }
    if (mul_overflow(a/gcd(a, b), b)) {
        print("Large");
        return;
    }
    ll ans = lcm(a, b);
    if (ans <= INF) {
        print(ans);
    } else {
        print("Large");
    }
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
