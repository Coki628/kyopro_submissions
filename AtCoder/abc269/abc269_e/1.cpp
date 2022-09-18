/*
・きっちり自力AC！
・インタラクティブ、二分探索
・縦横でにぶたん2回やる。下限ミスって1ペナ…。
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

// インタラクティブ用
ll ask(ll a, ll b, ll c, ll d) {
    ll res;
    cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << endl;
    cin >> res;
    return res;
}
void answer(ll x, ll y) {
    cout << "! " << x << ' ' << y << endl;
}

void solve() {
    ll N;
    cin >> N;

    ll x = bisearch_min(0, N, [&](ll m) {
        ll res = ask(1, m, 1, N);
        return res == m - 1;
    });
    ll y = bisearch_min(0, N, [&](ll m) {
        ll res = ask(1, N, 1, m);
        return res == m - 1;
    });
    answer(x, y);
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
