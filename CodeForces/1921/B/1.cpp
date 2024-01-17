/*
・きっちり自力AC！
・移動が2つ同時に処理できて得なので優先して、残ったのは普通に。
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
    ll N;
    cin >> N;
    string S, T;
    cin >> S >> T;

    map<pll, ll> C;
    rep(i, N) {
        C[{S[i] - '0', T[i] - '0'}]++;
    }
    ll movecnt = min(C[{0, 1}], C[{1, 0}]);
    C[{0, 1}] -= movecnt;
    C[{1, 0}] -= movecnt;
    ll ans = movecnt + C[{0, 1}] + C[{1, 0}];
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
