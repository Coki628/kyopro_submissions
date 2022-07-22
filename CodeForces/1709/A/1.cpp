/*
・きっちり自力AC！
・再帰で3回潜れたらOK。
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
    x--;
    auto A = LIST(3);
    rep(i, 3) A[i]--;

    auto rec = [&](auto&& f, ll i, ll d) {
        if (d == 3) {
            return true;
        }
        if (A[i] == -1) {
            return false;
        }
        return f(f, A[i], d+1);
    };
    if (rec(rec, x, 1)) YES();
    else NO();
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
