/*
・きっちり自力AC。
・ようは2辺が軸と平行だとダメなので、x,yに両方被りがあるかチェック。
　場合分けは面倒なのでsetに詰める。
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
    ll N = 3;
    set<ll> se1, se2;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        se1.insert(x);
        se2.insert(y);
    }

    if (se1.size() == 2 and se2.size() == 2) {
        NO();
    } else {
        YES();
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
