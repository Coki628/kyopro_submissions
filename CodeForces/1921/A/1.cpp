/*
・きっちり自力AC！
・X,Yそれぞれsetに詰める。
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
    Set<ll> X, Y;
    rep(i, 4) {
        ll x, y;
        cin >> x >> y;
        X.insert(x);
        Y.insert(y);
    }

    assert(X.size() == 2 and Y.size() == 2);
    ll len1 = X.back() - X.front();
    ll len2 = Y.back() - Y.front();
    ll ans = len1 * len2;
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
