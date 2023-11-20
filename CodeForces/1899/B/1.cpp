/*
・自力AC！
・約数全列挙の内側でNのループ回したら結構重い気がしてしまうが、それで大丈夫。
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
    vector<ll> A(N);
    cin >> A;

    ll ans = -INF;
    for (auto k : divisors(N)) {
        ll sm = 0, mn = INF, mx = -INF;
        rep(i, N) {
            sm += A[i];
            if ((i + 1) % k == 0) {
                chmin(mn, sm);
                chmax(mx, sm);
                sm = 0;
            }
        }
        ll res = mx - mn;
        chmax(ans, res);
    }
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
